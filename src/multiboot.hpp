#ifndef multiboot_hpp_included
#define multiboot_hpp_included 1

// See the multiboot specification :
// https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
struct multiboot
{
   uint32_t flags;               // required

   uint32_t mem_lower;           // present if flags[0] is set
   uint32_t mem_upper;           // present if flags[0] is set

   struct {                      // present if flags[1] is set
      uint8_t drive;             // present if flags[1] is set
      uint8_t part1;             // present if flags[1] is set
      uint8_t part2;             // present if flags[1] is set
      uint8_t part3;             // present if flags[1] is set
   } boot_device;                // present if flags[1] is set

   char *cmdline;                // present if flags[2] is set

   uint32_t mods_count;          // present if flags[3] is set
   struct {                      // present if flags[3] is set
      uint8_t *mod_start;        // present if flags[3] is set
      uint8_t *mod_end;          // present if flags[3] is set
                                 //
      char *string;              // present if flags[3] is set
                                 //
      uint32_t reserved;         // always 0
   } *mods_addr;                 // present if flags[3] is set

   struct                        // Present if flags[4] or flags[5] is set
   {                             //
      union {                    //
         uint32_t tabsize;       // Present if flags[4] is set
         uint32_t num;           // Present if flags[5] is set
      };                         //
      union {                    //
         uint32_t strsize;       // Present if flags[4] is set
         uint32_t size;          // Present if flags[5] is set
      };                         //
         uint8_t *addr;          // Present if flags[4] or flags[5] is set
      union {                    //
         uint32_t reserved;      // Present if flags[4] is set
         uint32_t shndx;         // Present if flags[5] is set
      };                         //
   } syms;                       // Present if flags[4] or flags[5] is set

   uint32_t mmap_length;         // Present if flags[6] is set
   struct {                      // Present if flags[6] is set
      uint32_t size() const {    // Present if flags[6] is set
         return reinterpret_cast <const uint32_t *>(this)[-1]; // Weird size(-4)
      }                          // Present if flags[6] is set
      uint32_t base_addr_low;    // Present if flags[6] is set
      uint32_t base_addr_high;   // Present if flags[6] is set
      uint32_t length_low;       // Present if flags[6] is set
      uint32_t length_high;      // Present if flags[6] is set
      uint32_t type;             // Present if flags[6] is set
   } *mmap_addr;                 // Present if flags[6] is set
   // TODO: Take the size() into account for indexing

   uint32_t drives_length;       // Present if flags[7] is set
   struct {                      // Present if flags[7] is set
      uint32_t size;             // Present if flags[7] is set
      uint8_t  drive_number;     // Present if flags[7] is set
      uint8_t  drive_mode;       // Present if flags[7] is set
      uint16_t drive_cylinders;  // Present if flags[7] is set
      uint8_t  drive_heads;      // Present if flags[7] is set
      uint8_t  drive_sectors;    // Present if flags[7] is set
      uint16_t drive_ports[1];   // Present if flags[7] is set
   } *drives_addr;               // Present if flags[7] is set
   // TODO: Take the size into account for indexing

   uint8_t *config_table;        // Present if flags[8] is set
   // TODO: Integrate the structure of the table

   char *boot_loader_name;       // Present if flags[9] is set

   struct {                      // Present if flags[10] is set
      uint16_t version;          // Present if flags[10] is set
      uint16_t cseg;             // Present if flags[10] is set
      uint32_t offset;           // Present if flags[10] is set
      uint16_t cseg_16;          // Present if flags[10] is set
      uint16_t dseg;             // Present if flags[10] is set
      uint16_t flags;            // Present if flags[10] is set
      uint16_t cseg_len;         // Present if flags[10] is set
      uint16_t cseg_16_len;      // Present if flags[10] is set
      uint16_t dseg_len;         // Present if flags[10] is set
   } *apm_table;                 // Present if flags[10] is set

   uint32_t vbe_control_info;    // Present if flags[11] is set
   uint32_t vbe_mode_info;       // Present if flags[11] is set
   uint16_t vbe_mode;            // Present if flags[11] is set
   uint16_t vbe_interface_seg;   // Present if flags[11] is set
   uint16_t vbe_interface_off;   // Present if flags[11] is set
   uint16_t vbe_interface_len;   // Present if flags[11] is set
   // TODO: Check length of vbe_interface_len
};

#endif
