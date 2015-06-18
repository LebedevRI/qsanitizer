TEMPLATE = subdirs

SUBDIRS += \
    LeakDescription \
    StackItemParserDefault \
    StackItemParserXml \
    StackItem \
    LeakItem

StackItem.depends = StackItemParserDefault
StackItem.depends = StackItemParserXml
LeakItem.depends = LeakDescription
LeakItem.depends = StackItem
