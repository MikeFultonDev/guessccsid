SRCDIR=src
BLDDIR=obj
BINDIR=bin

csource := $(shell find $(SRCDIR) -type f -name *.c)
cobjs   := $(patsubst $(SRCDIR)/%,$(BLDDIR)/%,$(csource:.c=.o))
objects := $(cobjs)
cdeps   := $(cobjs:.o=.d)
programs := $(BINDIR)/guessccsid

all: $(programs)
	
clean:
	rm -f $(objects) $(cdeps) $(programs)

$(BLDDIR)/%.d: $(SRCDIR)/%.c
	mkdir -p $(BLDDIR) ; \
	clang -MM -MT $@ $(CPPFLAGS) -MF $@ $<

include $(cdeps)

$(BLDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(BLDDIR) ;
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(BLDDIR)/%.o: $(SRCDIR)/%.s
	mkdir -p $(BLDDIR) ;
	$(AS) $(ASFLAGS) -I$(MACDIR) -o $@ $< >$(@D)/$*.lst

$(BINDIR)/guessccsid: $(objects)
	mkdir -p $(BINDIR) ;
	$(LD) $(LDFLAGS) -o $@ $^ >$@.llst

.PHONY: all clean
