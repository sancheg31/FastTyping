TEMPLATE = subdirs

SUBDIRS += \
    fast_typing_lib \
    fast_typing_tests \
    fast_typing_ui

fast_typing_tests.depends = fast_typing_lib
fast_typing_ui.depends = fast_typing_lib

message(project dir: $${PWD})
