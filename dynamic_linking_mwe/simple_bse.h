class ApiObject {
  public:
    bool Close();
  protected:
    virtual bool DoClose() = 0;
};

bool ApiObject::Close() {
  printf("ApiObject::Close\n");
  DoClose();
  return true;
}