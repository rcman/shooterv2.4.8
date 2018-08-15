##
## SConstruct
## this scons build script produces the executable for the project
################################################################################
## a little preparation for building an SDL project
buildEnv = Environment(CCFLAGS = '-g -Wall')
buildEnv.ParseConfig('sdl-config --cflags --libs')
projectConfig = {}
################################################################################
## this is the file name of the executable file to output
projectConfig['executable'] = 'GameExe'
################################################################################
## if you need to look in special folders for include files add them here
projectConfig['include path'] = Split("""
	.
	./include/
	""")
################################################################################
## if your libs are in special locations set their paths here
projectConfig['library path'] = Split("""
	""")
################################################################################
## if you need to link against other libs, add them here
projectConfig['libraries'] = Split("""
	SDL_image SDL_mixer SDL_ttf
	""") + buildEnv['LIBS']
################################################################################
## add your sources for your project here
projectConfig['sources'] = Glob('src/*.cpp')
################################################################################
## this is what builds the project executable
buildEnv.Program('release/' + projectConfig['executable'],
	projectConfig['sources'],
	LIBS = projectConfig['libraries'],
	LIBPATH = projectConfig['library path'],
	CPPPATH = projectConfig['include path'])
################################################################################
