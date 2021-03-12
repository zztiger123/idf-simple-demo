LIBS += beurerMUSalgorithm

COMPONENT_ADD_LDFLAGS += -L $(COMPONENT_PATH)/lib $(addprefix -l,$(LIBS))
