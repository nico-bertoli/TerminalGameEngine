from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class TermeConan(ConanFile):
    #----------------------------- package info
    name = "terme"
    version = "1.0.0"
    description = "An engine for developing terminal games"
    license = "MIT" 
    author = "Nicolò Bertoli <nicobertoli.1999@gmail.com>"
    url = "https://github.com/nico-bertoli/terme"
    
    #-----------------------------
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt", "terme/*"
    
    def requirements(self):
        self.requires("nbkit/1.0.0@local/stable")
        self.requires("sfml/2.6.2")
    
    def configure(self):
        if "sfml" in self.options:
            self.options["sfml"].shared = False
    
    def layout(self):
        cmake_layout(self)
    
    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    
    def package(self):
        cmake = CMake(self)
        cmake.install()
    
    def package_info(self):
        self.cpp_info.libs = ["terme"]
        if self.settings.os == "Linux":
            self.cpp_info.system_libs = ["X11"]
