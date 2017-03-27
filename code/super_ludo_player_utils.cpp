#include "super_ludo_player.h"

using namespace std;

bitset<64> super_ludo_player::double_to_bitset(double input_double){
  data.input = input_double;
  bitset<64>   bits(data.output);
  return bits;
}

double super_ludo_player::bitset_to_double(bitset<64> input_set){
  uint64_t const u = input_set.to_ullong();
  double d;

  // Aliases to `char*` are explicitly allowed in the Standard (and only them)
  char const* cu = reinterpret_cast<char const*>(&u);
  char* cd = reinterpret_cast<char*>(&d);

  // Copy the bitwise representation from u to input_set
  memcpy(cd, cu, sizeof(u));
  return d;
}

void super_ludo_player::debug_stop(std::string action, int pos, bool cout_positions){
 std::cout << "Can " << action << " with DiceRoll: " << dice_roll << std::endl;
 std::cout << "Current Player pos: " << pos << std::endl;
 if (cout_positions) {
   for (int i = 0; i < pos_start_of_turn.size(); i++) {
     std::cout << "Debug_pos " << i << ": " << pos_start_of_turn[i] << std::endl;
   }
 }
 std::cout << "Press ENTER to continue" << std::endl;
 std::cin.ignore(std::cin.rdbuf()->in_avail()+1);
}

std::vector < int > super_ludo_player::sorted_index(fann_type* calc_out){
  double fourth_largest = 0;
  double third_largest = 0;
  double second_largest = 0;
  double largest = 0;
  int fourth_largest_index = -1;
  int third_largest_index = -1;
  int second_largest_index = -1;
  int largest_index = -1;
  //Finding Largest
  for (int i = 0; i < 4; ++i)
    if (calc_out[i]>largest){
      largest = calc_out[i];
      largest_index = i;
    }
  //finding second largset
  for (int i = 0; i < 4; ++i)
   if (calc_out[i]>second_largest){
      if (calc_out[i] == largest)
            continue;
      second_largest = calc_out[i];
      second_largest_index = i;
   }
  //finding third largset
  for (int i = 0; i < 4; ++i)
   if (calc_out[i]>third_largest){
      if (calc_out[i] == largest || calc_out[i] == second_largest)
            continue;
      third_largest = calc_out[i];
      third_largest_index = i;
   }
  //finding fourth largset
  for (int i = 0; i < 4; ++i)
   if (calc_out[i]>third_largest){
      if (calc_out[i] == largest || calc_out[i] == second_largest || calc_out[i] == third_largest)
            continue;
      fourth_largest = calc_out[i];
      fourth_largest_index = i;
   }

   return vector<int>{largest_index,second_largest_index,third_largest_index,fourth_largest_index};
}