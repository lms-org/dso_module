from conans import ConanFile, CMake

        #TODO does not work, just used to get lms
class DsoModuleConan(ConanFile):

    name = "dso_module"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    exports = "include/*","src/*","README.md","CMakeLists.txt","configs/*"
    requires = "lms/2.0@lms/stable"
    generators = "cmake"

    def build(self):
        cmake = CMake(self.settings)
        self.run('cmake %s %s' % (self.conanfile_directory, cmake.command_line))
        self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.so",dst="bin")
