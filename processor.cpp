#include "simulator.hpp"

// =====================================================================
btb_t::btb_t()
{};

// =====================================================================
bool btb_t::fetch(uint64_t branch_addr)
{
  uint64_t btb_index = branch_addr & 1023;
  for (int i = 0; i < 4; ++i)
    if (set_assoc_cache[i][btb_index].res_addr == branch_addr)
      return true;

  return false;
}

// =====================================================================
void btb_t::store(uint64_t branch_addr)
{
  uint64_t btb_index = branch_addr & 1023;

  uint32_t LRU = 0;
  for (int i = LRU; i < 4; ++i)
    if (set_assoc_cache[LRU][btb_index].timestamp
          < set_assoc_cache[i][btb_index].timestamp)
      LRU = i;

  set_assoc_cache[LRU][btb_index].res_addr = branch_addr;
}

// =====================================================================
processor_t::processor_t()
{
  pipeline_depth = 19;
  penalty = pipeline_depth;
};

// =====================================================================
void processor_t::allocate(){};

// =====================================================================
void processor_t::clock()
{
  if (!skiping_cycles)
  {
    opcode_package_t new_instruction;
    if (!orcs_engine.trace_reader->trace_fetch(&new_instruction))
      orcs_engine.simulator_alive = false;
    else
      if (new_instruction == INSTRUCTION_OPERATION_CODE)
        if (!branch_addr_res.fetch(branch_addr))
	{
            skiping_cycles = penalty;
            branch_addr_res.store(branch_addr);
        }
  }
  else
  {
    --skiping_cycles;
  }
};

// =====================================================================
void processor_t::statistics()
{
	ORCS_PRINTF("######################################################\n");
	ORCS_PRINTF("processor_t\n");

};
