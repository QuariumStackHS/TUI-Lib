#include <AES.h>
#include <iostream>
#include <time.h>
using namespace std;
unsigned char *gen_IV(){

    unsigned char iv[16];
    for(int i=0;i<=15;i++){
        iv[i]=rand() % 255 + 1;
    }
    return iv;
}
unsigned char *Gen_Key(unsigned char key[32]){
    for(int i=0;i<=31;i++){
        key[i]=rand() % 255 + 1;
    }
    return key;
}
const unsigned int BLOCK_BYTES_LENGTH = 16 * sizeof(unsigned char);
int main(){
  srand (time(NULL));
  AES aes(256);
  unsigned char plain[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  cout<<(char *)plain<<endl;
  unsigned char *iv = gen_IV();
  unsigned char key[32];
  Gen_Key(key);
  cout<<sizeof(iv)<<endl;
  unsigned int len;
  
  unsigned char *out = aes.EncryptCBC(plain, BLOCK_BYTES_LENGTH, key, iv, len);
  cout<<hex<<out<<endl;
  unsigned char *innew = aes.DecryptCBC(out, BLOCK_BYTES_LENGTH, key, iv);
  cout<<(char*)innew<<endl;
  //ASSERT_FALSE(memcmp(innew, plain, BLOCK_BYTES_LENGTH));
  delete[] out;
  delete[] innew;
}