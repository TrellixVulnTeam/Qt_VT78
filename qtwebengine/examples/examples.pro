TEMPLATE=subdirs

qtHaveModule(webengine) {
    SUBDIRS += webengine/quicknanobrowser
}

qtHaveModule(webenginewidgets) {
    SUBDIRS += \
        webenginewidgets/demobrowser \
        webenginewidgets/fancybrowser \
        webenginewidgets/markdowneditor
}
