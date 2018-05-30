#include "../include/class_reg_32.h"

class_reg_32::class_reg_32()
{
}
class_reg_32::class_reg_32(int mask) : mask(mask)
{
}
class_reg_32::class_reg_32(int mask, int reg_value) : mask(mask), reg_value(reg_value)
{
}

void class_reg_32::set_reg_value(int data){
  reg_value = data;
}

void class_reg_32::write(int reg_value){
  set_reg_value(reg_value);
}

int class_reg_32::read(){
  return reg_value;
}

void class_reg_32::reset(){

}
