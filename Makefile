target = egg
src = $(wildcard *.cpp) \
			$(wildcard src/*.cpp)
obj = $(src:.cpp=.o) 
dep = $(obj:.o=.d)
PREFIX = /usr/local

CXX = clang++

LDFLAGS = -lboost_program_options $(libsdl)

CXXFLAGS = -std=c++1z -g -Wall  $(sdlheader)

ifeq ($(shell uname -s), Darwin)
	libsdl = -framework SDL2 -framework SDL2_mixer
	sdlheader = -I /Library/Frameworks/SDL2.framework/Headers \
		-I /Library/Frameworks/SDL2_mixer.framework/Headers
else
	libsdl = -lSDL2 -lSDL2_mixer
	sdlheader = -I /usr/include/SDL2
endif


$(target): $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS)

-include $(dep)

%.d: %.c
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -rf $(obj) $(target)*

.PHONY: cleandep
cleandep:
	rm -f $(dep)


.PHONY: install
install: $(target)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $< $(DESTDIR)$(PREFIX)/bin/$(target)

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(target)