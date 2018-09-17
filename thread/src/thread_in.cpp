#include "common_var.h"
#include "thread_in.h"
#include "tetris.h"

// ========================================================================================================
// =========================================== extern global variables ====================================
// ========================================================================================================
std::mutex mtx;
std::condition_variable can_play;
std::condition_variable can_read;

bool SHARED_PLAYING;

bool SHARED_RUNNING;
char SHARED_KEY_OUTPUT;

// ========================================================================================================
// ================================================== functions ===========================================
// ========================================================================================================

// joystick manipulation -------------------------------------------------------------------

// return KEY value based on the combination of input reading
char get_combination(std::string &confirm,  std::string &axis,  std::string &direction){
  if(confirm.compare("1") == 0){
    if(axis.compare("1") == 0){
      if(direction.compare("1") == 0)
        return TOP_KEY;
      else
        return DOWN_KEY;
    }
    else{
      if(direction.compare("1") == 0)
        return LEFT_KEY;
      else
        return RIGHT_KEY;
    }
  }
  return NO_KEY;
}

// decode analogical value into high (1) or low (0)
std::string analog_to_digital(std::string &an_value){
  int val = std::stoi(an_value);
  std::string str_val = "0"; // default
  if(val > ANALOGIC_MID){
    str_val = "1";
  }
  return str_val;
}

// file manipulation -------------------------------------------------------------------
void write_value(const char* filename, char value){
  std::fstream outData;
  outData.open(filename, std::fstream::out);
  if (outData.is_open()){
    outData << value;
    outData.close();
  }
  else throw std::runtime_error("[write_value]: could not open file.");
}

std::string read_value(const char* filename){
  std::fstream inData;
  inData.open(filename, std::fstream::in);
  if (inData.is_open()){
    std::string str;
    inData >> str;
    inData.close();
    return str;
  }
  throw std::runtime_error("[read_value]: could not open file.");
}

// aux -------------------------------------------------------------------

void prepare_inputs(){
  INPUTS.push_back(pot);
  INPUTS.push_back(pbu);
  INPUTS.push_back(ldr);

  // fill bbb_inputs name
  INPUTS[in_name::POTENCI].name = "pot";
  INPUTS[in_name::PBUTTON].name = "pbt";
  INPUTS[in_name::LDRESIS].name = "ldr";

  // fill bbb_inputs path
  INPUTS[in_name::POTENCI].path = POTENCI_PATH;
  INPUTS[in_name::PBUTTON].path = PBUTTON_PATH;
  INPUTS[in_name::LDRESIS].path = LDRESIS_PATH;

  // fill bbb_inputs read
  for( bbb_input &bbb_in: INPUTS){
      bbb_in.value = read_value((bbb_in.path).c_str());
  }
}


// THREAD =========================================================================================

void print_values(){
  for(bbb_input &bbb_in: INPUTS){
    std::cout << bbb_in.name << ": " << bbb_in.value << " ";
  }
  std::cout << std::endl;
}

void check_inputs(){
  while(SHARED_RUNNING){
    // THREAD LOCK ===========================================
    std::unique_lock<std::mutex> lck(mtx);
    while(SHARED_PLAYING) can_read.wait(lck);
    // =======================================================

    // read
    std::string temp_value;
    bool value_change = false;
    for( bbb_input &bbb_in: INPUTS){
      temp_value = read_value((bbb_in.path).c_str());

      if(temp_value.compare("0") != 0 && temp_value.compare("1") != 0) // transform analog into digital value if necessary
        temp_value = analog_to_digital(temp_value);
      if(temp_value.compare(bbb_in.value) != 0){ // if new value is different from previous value
        bbb_in.value = temp_value;
        value_change = true;
      }
    }
    if(value_change){
      value_change = false; // reset

      //print_values();

      // write new KEY value from new combination if necessary
      char new_KEY_OUTPUT = get_combination(
        INPUTS[in_name::PBUTTON].value, INPUTS[in_name::POTENCI].value, INPUTS[in_name::LDRESIS].value);
      //std::cout << "NEW_KEY: " << new_KEY_OUTPUT << std::endl;
      if (SHARED_KEY_OUTPUT != new_KEY_OUTPUT){
        SHARED_KEY_OUTPUT = new_KEY_OUTPUT;
        //write_value(JOYSTICK_PATH,KEY_OUTPUT);
        //print new key
        //std::cout << "KEY: " << KEY_OUTPUT << std::endl;
      }
    }
    //std::this_thread::sleep_for (std::chrono::milliseconds(500));

    // THREAD UNLOCK ===========================================
    SHARED_PLAYING = true;
    can_play.notify_one();
    // =======================================================
  } 
}

// main tests -------------------------------------------------------------------

int main() {
  prepare_inputs();
  SHARED_PLAYING = true;
  SHARED_RUNNING = true;
  SHARED_KEY_OUTPUT = 'a';

  std::thread t1(check_inputs);
  std::thread t2(game);
  
  t2.join();  // game ended

  SHARED_PLAYING = false;
  t1.join();
  
  return 0;
}