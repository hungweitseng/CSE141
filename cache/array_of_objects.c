#include <stdio.h>
#include <stdlib.h>

struct grades
{
  int id;
  double *homework;
  double average;
};

int main(int argc, char **argv)
{
  struct grades *gradesheet;
  int i,j; 
  int total_number_students = 28800;
  int homework_items = 10000;
  double average = 0;
  if(argc >= 3)
  {
    total_number_students = atoi(argv[1]);
    homework_items = atoi(argv[2]);
  }
  else
  {
    fprintf(stderr,"%s total_number_students homework_items",argv[0]);
    exit(1);
  }

  gradesheet = (struct grades *)malloc(total_number_students*sizeof(struct grades));

  for(i=0;i<total_number_students; i++)
  {
    gradesheet[i].homework = (double *)malloc(total_number_students*sizeof(double));
    for(j=0;j<homework_items;j++)
      gradesheet[i].homework[j] = rand();
  }
  
  for(i=0;i<total_number_students; i++)
  {
      average = 0.0;
      for(j=0;j<homework_items;j++)
      {
        average+=gradesheet[i].homework[j];
      }
      gradesheet[i].average = average/homework_items;
  }
  
  return 0;
}
