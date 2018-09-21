# CMake generated Testfile for 
# Source directory: /home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-source/avs-device-sdk/RegistrationManager/test
# Build directory: /home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/RegistrationManager/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(CustomerDataManagerTest.testEmptyManager "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/RegistrationManager/test/CustomerDataManagerTest" "--gtest_filter=CustomerDataManagerTest.testEmptyManager")
add_test(CustomerDataManagerTest.testClearData "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/RegistrationManager/test/CustomerDataManagerTest" "--gtest_filter=CustomerDataManagerTest.testClearData")
add_test(CustomerDataManagerTest.testClearDataAfterHandlerDeletion "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/RegistrationManager/test/CustomerDataManagerTest" "--gtest_filter=CustomerDataManagerTest.testClearDataAfterHandlerDeletion")
add_test(RegistrationManagerTest.testLogout "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/RegistrationManager/test/RegistrationManagerTest" "--gtest_filter=RegistrationManagerTest.testLogout")
