#ifndef FTRACE_SYMBOL_H
#define FTRACE_SYMBOL_H

struct sym {
	unsigned long addr;
	unsigned long size;
	char *name;
};

#define SYMTAB_GROW  16

struct symtab {
	struct sym *sym;
	struct sym **sym_names;
	size_t nr_sym;
	size_t nr_alloc;
};

#define START_MAPS "[[[MAP START]]]"
#define END_MAPS   "[[[MAP END  ]]]"
#define MAPS_MARKER ((void *)0xbaaddaad)

struct ftrace_proc_maps {
	struct ftrace_proc_maps *next;
	uint64_t start;
	uint64_t end;
	char prot[4];
	uint32_t len;
	char libname[];
};

struct sym * find_symtab(unsigned long addr, struct ftrace_proc_maps *maps);
struct sym * find_symname(const char *name);
void load_symtabs(const char *filename);
void unload_symtabs(void);
void print_symtabs(void);

struct sym * find_dynsym(size_t idx);
size_t count_dynsym(void);
int load_dynsymtab(const char *filename);
void unload_dynsymtab(void);

char *symbol_getname(struct sym *sym, unsigned long addr);
void symbol_putname(struct sym *sym, char *name);

void setup_skip_idx(void);
void destroy_skip_idx(void);
bool should_skip_idx(unsigned idx);

#endif /* FTRACE_SYMBOL_H */
