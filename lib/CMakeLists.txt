

set(SOURCE_FILES
        Format.cpp
        PlaceholderPosition.cpp
        FormatArgsMerger.cpp
        InvalidFormat.cpp
        Tokenization.cpp
        Token.cpp
)
set(HEADER_FILES
        Format.h
        PlaceholderPosition.h
        FormatArgsMerger.h
        Token.h
        InvalidFormat.h
        Tokenization.h
)
set(TEMPLATE_FILES
        Format.tpp
        FormatArgsMerger.tpp
)

add_library(NiceGraphic_FormatOutput ${SOURCE_FILES} ${HEADER_FILES} ${TEMPLATE_FILES})
target_include_directories(NiceGraphic_FormatOutput INTERFACE ${CMAKE_CURRENT_LIST_DIR})