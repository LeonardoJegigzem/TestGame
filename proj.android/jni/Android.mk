LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_CPPFLAGS += -fexceptions #Agregado para evitar problemas con la compilacion de rapidxml :/

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameLayer.cpp \
				   ../../Classes/hud/JoystickLayer.cpp \
				   ../../Classes/input/InputManager.cpp \
				   ../../Classes/input/util/InputFactory.cpp \
				   ../../Classes/infra/context/Context.cpp \
				   ../../Classes/infra/graphics/GPU_TC.cpp \
				   ../../Classes/infra/graphics/ResolutionSupport.cpp \
				   ../../Classes/entity/Entity.cpp \
				   ../../Classes/player/Player.cpp \
				   ../../Classes/player/Status.cpp \
				   ../../Classes/player/AnimationHandler.cpp  \
				   ../../Classes/player/utils/MapUtils.cpp \
				   ../../Classes/player/utils/factory/PlayerFactory.cpp \
				   ../../Classes/player/triggers/Trigger.cpp \
				   ../../Classes/player/animation/AnimationStore.cpp \
				   ../../Classes/character/Character.cpp \
				   ../../Classes/character/weapon/Weapon.cpp \
				   ../../Classes/character/weapon/factory/WeaponFactory.cpp \
				   ../../Classes/collision/CollisionHandler.cpp \
				   ../../Classes/level/LevelManager.cpp  \
				   ../../Classes/level/LevelBackground.cpp \
				   ../../Classes/level/LevelElements.cpp \
				   ../../Classes/level/Level.cpp \
				   ../../Classes/level/config/LevelConfig.cpp \
				   ../../Classes/level/config/descriptors/BackgroundDescriptor.cpp \
				   ../../Classes/level/config/descriptors/ElementsDescriptor.cpp \
				   ../../Classes/level/config/descriptors/PlayerDescriptor.cpp \
				   ../../Classes/level/config/descriptors/AnimationsDescriptor.cpp \
				   ../../Classes/level/config/descriptors/AnimationDescriptor.cpp \
				   ../../Classes/level/config/descriptors/WeaponDescriptor.cpp \
				   ../../Classes/thirdparty/sneakyjoystick/SneakyButton.cpp \
				   ../../Classes/thirdparty/sneakyjoystick/SneakyButtonSkinnedBase.cpp \
				   ../../Classes/thirdparty/sneakyjoystick/SneakyJoystick.cpp \
				   ../../Classes/thirdparty/sneakyjoystick/SneakyJoystickSkinnedBase.cpp
				   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
