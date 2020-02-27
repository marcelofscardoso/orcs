// ============================================================================
// ============================================================================
class btb_t
{
  public:
    btb_t();

    bool fetch(uint64_t);
    void store(uint64_t);

  private:
    struct line_t
    {
      uint64_t resolved_addr;
      uint32_t timestamp;
    };

    struct line_t set_assoc_cache_[4][1024];
};

class processor_t
{
  public:
    // ========================================================================
    // Methods
    // ========================================================================
    processor_t();

    void allocate();
    void clock();
    void statistics();

  private:
    int penalty;
    int pipeline_depth;
    btb_t branch_addr_resolution;
};

