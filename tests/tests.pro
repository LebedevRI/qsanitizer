TEMPLATE = subdirs

SUBDIRS += \
    LeakDescription \
    StackItem \
    LeakItem

LeakItem.depends = LeakDescription
LeakItem.depends = StackItem
