LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../Classes/AppDelegate.cpp \
					../../Classes/Background.cpp \
					../../Classes/BackGround3Parts.cpp \
					../../Classes/BaseGameLayer.cpp \
					../../Classes/BaseMenuLayer.cpp \
					../../Classes/BasicEnemy.cpp \
					../../Classes/Blizzard.cpp \
					../../Classes/Cloud.cpp \
					../../Classes/CustomAudioManager.cpp \
					../../Classes/EnemyBullet.cpp \
					../../Classes/EnemyBulletSmart.cpp \
					../../Classes/GameManager.cpp \
					../../Classes/HealthParticle.cpp \
					../../Classes/HeightEnemy.cpp \
					../../Classes/Level1.cpp \
					../../Classes/Level2.cpp \
					../../Classes/Level3.cpp \
					../../Classes/Level4.cpp \
					../../Classes/Level5.cpp \
					../../Classes/Level6.cpp \
					../../Classes/Level7.cpp \
					../../Classes/Level8.cpp \
					../../Classes/Level9.cpp \
					../../Classes/MainMenuLayer.cpp \
					../../Classes/MediumEnemy.cpp \
					../../Classes/OptionsLayer.cpp \
					../../Classes/Player.cpp \
					../../Classes/PlayerBullet.cpp \
					../../Classes/PlayerBulletx2.cpp \
					../../Classes/PlayerBulletx3.cpp \
					../../Classes/PlayerUpgradeParticle.cpp \
					../../Classes/PlayerUpgradeParticle2.cpp \
					../../Classes/SelectMenuLayer.cpp \
					../../Classes/TouchController.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
