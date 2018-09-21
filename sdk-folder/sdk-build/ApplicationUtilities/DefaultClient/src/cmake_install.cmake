# Install script for directory: /home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-source/avs-device-sdk/ApplicationUtilities/DefaultClient/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libDefaultClient.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libDefaultClient.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libDefaultClient.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libDefaultClient.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ApplicationUtilities/DefaultClient/src/libDefaultClient.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libDefaultClient.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libDefaultClient.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/lib/libDefaultClient.so"
         OLD_RPATH "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/AIP/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/Alerts/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/Bluetooth/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/InteractionModel/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/Notifications/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/PlaybackController/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/SpeakerManager/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/SpeechSynthesizer/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/Settings/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/TemplateRuntime/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/AudioPlayer/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/ExternalMediaPlayer/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilityAgents/System/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ADSL/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/AFML/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ApplicationUtilities/Resources/Audio/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CertifiedSender/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/RegistrationManager/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ACL/src:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/AVSCommon:/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/third-party/usr/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/opt/android-ndk-r10d/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip" "$ENV{DESTDIR}/usr/local/lib/libDefaultClient.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local" TYPE DIRECTORY FILES "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-source/avs-device-sdk/ApplicationUtilities/DefaultClient/include")
endif()

