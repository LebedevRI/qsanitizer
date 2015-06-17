TEMPLATE = subdirs

SUBDIRS += \
    LeakDescription \
    StackItem \
    LeakItem \
    StackItemParserXml

LeakItem.depends = LeakDescription
LeakItem.depends = StackItem
