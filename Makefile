# Mohammed Seghir Said  

ODIR = bin
CFLAGS=-c -g 
HEADDIR = Header
SOURCEDIR = Sources


compil: $(ODIR)/ScheduleKey.o $(ODIR)/DES_permutation.o $(ODIR)/bits_manip.o $(ODIR)/get_K.o $(ODIR)/Des.o $(ODIR)/F_function.o $(ODIR)/get_K16.o  $(ODIR)/main.o 
	gcc $^ -o AttackRun

run: AttackRun 
	./AttackRun

$(ODIR)/main.o: $(SOURCEDIR)/main.c $(HEADDIR)/get_K16.h $(HEADDIR)/ScheduleKey.h $(HEADDIR)/F_function.h $(HEADDIR)/Mon_message.h $(HEADDIR)/get_K.h $(HEADDIR)/Des.h
	gcc $(CFLAGS) -o $@ $(SOURCEDIR)/main.c 

$(ODIR)/ScheduleKey.o: $(SOURCEDIR)/ScheduleKey.c $(HEADDIR)/DES_permutation.h $(HEADDIR)/Tables_Of_Permutation.h
	gcc $(CFLAGS) -o $@ $(SOURCEDIR)/ScheduleKey.c 

$(ODIR)/DES_permutation.o: $(SOURCEDIR)/DES_permutation.c  
	gcc $(CFLAGS) -o $@ $(SOURCEDIR)/DES_permutation.c 
	
$(ODIR)/bits_manip.o: $(SOURCEDIR)/bits_manip.c $(HEADDIR)/bits_manip.h $(HEADDIR)/Tables_Of_Permutation.h
	gcc $(CFLAGS) -o $@ $(SOURCEDIR)/bits_manip.c 

$(ODIR)/get_K.o: $(SOURCEDIR)/get_K.c $(HEADDIR)/Des.h $(HEADDIR)/DES_permutation.h $(HEADDIR)/ScheduleKey.h $(HEADDIR)/F_function.h $(HEADDIR)/Tables_Of_Permutation.h 
	gcc $(CFLAGS) -o $@ $(SOURCEDIR)/get_K.c 

$(ODIR)/Des.o: $(SOURCEDIR)/Des.c $(HEADDIR)/DES_permutation.h $(HEADDIR)/ScheduleKey.h $(HEADDIR)/F_function.h $(HEADDIR)/Tables_Of_Permutation.h
	gcc $(CFLAGS) -o $@ $(SOURCEDIR)/Des.c 

$(ODIR)/F_function.o: $(SOURCEDIR)/F_function.c $(HEADDIR)/DES_permutation.h $(HEADDIR)/F_function.h $(HEADDIR)/Tables_Of_Permutation.h $(HEADDIR)/bits_manip.h
	gcc $(CFLAGS) -o $@ $(SOURCEDIR)/F_function.c 

$(ODIR)/get_K16.o: $(SOURCEDIR)/get_K16.c $(HEADDIR)/DES_permutation.h $(HEADDIR)/ScheduleKey.h $(HEADDIR)/F_function.h $(HEADDIR)/Tables_Of_Permutation.h
	gcc $(CFLAGS) -o $@ $(SOURCEDIR)/get_K16.c 


	
clean: 
	rm -f bin/*.o
	rm -f AttackRun


	
