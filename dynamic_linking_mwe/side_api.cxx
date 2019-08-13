#include <cstdio>
#include <vector>
#include <cstdlib>
#include "side_api.h"
#include "simple_bse.h"

class ConcreteApiObject : public ApiObject {
public:
  ConcreteApiObject(int size) : m_data(new double[size]) {}

protected:
  bool DoClose();

private:
  double* m_data;
};

bool ConcreteApiObject::DoClose() {
  printf("Deleting the data\n");
  if (m_data) {
    delete[] m_data;
  }
  return true;
}

class ConcreteApiObjectVector {
public:
  bool Add(ConcreteApiObject* obj);
  bool Close();
  size_t GetSize();
  ConcreteApiObject* Get(size_t i);
private:
  std::vector<ConcreteApiObject*> m_objects;
};

bool ConcreteApiObjectVector::Close() {
  for (auto o : m_objects) {
    o->Close();
  }
  return true;
}

bool ConcreteApiObjectVector::Add(ConcreteApiObject* obj) {
  m_objects.push_back(obj);
  return true;
}

size_t ConcreteApiObjectVector::GetSize() {
  return m_objects.size();
}

ConcreteApiObject* ConcreteApiObjectVector::Get(size_t i) {
  return m_objects[i];
}


ConcreteApiObjectVector* CreateApiList(int size) {
  printf("Creating list\n");
  ConcreteApiObjectVector* list = new ConcreteApiObjectVector();
  for (int i = 0; i < size; i++) {
    list->Add(new ConcreteApiObject(rand() % 20));
  }
  return list;
}

bool CloseList(ConcreteApiObjectVector* list) {
  printf("Closing list\n");
  bool ret = list->Close();
  printf("List closed\n");
  return ret;
}