TEMPLATE = subdirs
SUBDIRS += \
    src/abalonecore \
    src/tui \
    src/gui \
    tests \    

src-tui.depends = src/abalonecore
tests.depends = src/abalonecore
src-gui.depends = src/abalonecore

OTHER_FILES += config.pri \
    Doxyfile \
