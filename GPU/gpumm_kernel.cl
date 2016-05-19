__kernel void
matrix_mul(__global float* input_a,
           __global float* input_b,
           __global float* output,
           int size)
{
   int col = get_global_id(0);
   int row = get_global_id(1);

   float value = 0;
   for (int k = 0; k < size; ++k)
   {
      float elementA = input_a[row * size + k];
      float elementB = input_b[k * size + col];
      value += elementA * elementB;
   }
   output[row * size + col] = value;
}
