#include <pthread.h>
#include <stdlib.h>
#include <spdlog/spdlog.h>
#include <assert.h>
static pthread_key_t key;

int main(int argc, char** argv) {
  auto val = new int{100};
  pthread_key_create(&key, NULL);

  if(auto ret = pthread_setspecific(key, val); ret)
  {
    SPDLOG_ERROR("set specific key  fail");
    pthread_key_delete(key);
    return -1;
  }

  auto capture_value = static_cast<int*>(pthread_getspecific(key));

  assert(capture_value == val);

  pthread_key_delete(key);

  return 0;
}