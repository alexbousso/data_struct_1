CC = g++
OBJS_EXEC = main1.o application.o
EXEC = iDroid
ALL_EXECS = $(EXEC) application_test
OBJS_APPLICATION_TEST = application.o application_test.o
DEBUG_FLAG = # assign -g for debug
LIB = #-L.
CFLAGS = -std=c++0x -pedantic-errors -Werror -Wall $(DEBUG_FLAG) -DNDEBUG

$(EXEC) : $(OBJS_EXEC)
	$(CC) $(OBJS_EXEC) -o $@ $(LIB)

tests : application_test

application_test : $(OBJS_APPLICATION_TEST)
	$(CC) $(OBJS_APPLICATION_TEST) -o $@ $(LIB)

application.o: application.cpp application.h exceptions.h

main1.o: main1.cpp library1.h

application_test.o: Tests/application_test.cpp Tests/../application.h \
 Tests/assert.h Tests/test_utils.h Tests/../exceptions.h
	$(CC) -c $(CFLAGS) ./Tests/$*.cpp

clean : 
	rm -f $(OBJS_EXEC) $(OBJS_APPLICATION_TEST) $(ALL_EXECS) 

