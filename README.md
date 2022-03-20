# NiceFormatter

This is a library which provides a function called "Format". This function provides 
a comfortable way to insert values of variables into a string.

## How to integrate it

You can integrate this library into your build process in cmake.

1. Add this respo via "git add submodule"
2. Add it to your build process via add_subdirectory(<path-to-library>/lib).
3. Link to this library via target_link_libraries(<your-build-target> PRIVATE NiceGraphic_FormatOutput)

NiceGraphic_FormatOutput is the name of the target for this library.

It is build in c17++ with help of cmake. 

## How to use

See [Tutorial](docs/manual.md) for how to use it.

