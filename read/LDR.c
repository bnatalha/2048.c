#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h> // open(), O_RDONLY
#include <unistd.h> // read(), sleep()
#include <string.h> // memcpy()

#define BUFFER_LENGTH       5
#define INT_BUFFER_LENGTH   5
#define VALUE_MAX           512
#define TOLERANCE           50

int main()
{
  int temp = 0;
  //key[KEY_A] = 1;
  while(1)
  {
    char file_name[VALUE_MAX];
    char potenFile[VALUE_MAX];
    int value;
    char buffer[BUFFER_LENGTH];
    char intBuffer[INT_BUFFER_LENGTH];
    int fd;
    
    // Copiar o path para file_name
    sprintf(file_name, "/sys/bus/iio/devices/iio:device0/in_voltage0_raw");
    // Abrindo o arquivo e verificando se houve erro
    fd = open(file_name, O_RDONLY);

    if (fd == -1) {
      printf("O arquivo %s não abriu\n", file_name);
      return(-1);
    }

    // Lendo o conteúdo do arquivo para o buffer
    if (read(fd, buffer, BUFFER_LENGTH) == -1) {
      printf("Não foi possível carregar o conteudo para buffer\n");
      return(-1);
    }
    close(fd);

    //memcpy(intBuffer, buffer, BUFFER_LENGTH);
    buffer[BUFFER_LENGTH-1] = '\0';
    value = atoi(buffer);
    
    if (value < 4000)
    {
      // fprintf(68); ou fprintf(67)
      printf("LDR = %d\n", value);
      temp = value;
    }
    sleep(0.5);
  }
    return 0;
}

