# for sub makefile
#-------------------------------------------------------------------------------
#                                  globals
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
#                                  binaries
#-------------------------------------------------------------------------------

# db main program
bin_SCRIPTS = db 
bin_SCRIPTS += tools.py

# helper programs
tooldir = $(libexecdir)
tool_DATA = dbgo dbcc

# alias file
aliasdir = $(libexecdir)
alias_DATA = db_envsetup
db_envsetup:
	echo "alias dbc='. $(tooldir)/dbcc $$1'" > $@
	echo "alias dbgo='. $(tooldir)/dbgo'" >> $@
	echo -e "export PATH=$(bindir):\x24{PATH}" >> $@
CLEANFILES = db_envsetup

# db_firstrun program
bin_SCRIPTS += db_firstrun 
CLEANFILES += db_firstrun

db_firstrun: part1 part2
	$(INSTALL) -m 755 $< $@
	echo "tooldir=$(tooldir)" >> $@
	cat part2 >> $@

