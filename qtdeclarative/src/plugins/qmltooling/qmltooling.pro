TEMPLATE = subdirs

SUBDIRS += \
    qmldbg_debugger \
    qmldbg_local \
    qmldbg_profiler \
    qmldbg_server \
    qmldbg_tcp

qtHaveModule(quick): SUBDIRS += qmldbg_inspector
