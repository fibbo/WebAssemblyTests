double* new_double(int size)
{
  double* d = new double(size);
  for (int i = 0; i<size; i++)
  {
    d[i] = i;
  }
  return d;
}
