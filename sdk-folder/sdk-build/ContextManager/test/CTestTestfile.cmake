# CMake generated Testfile for 
# Source directory: /home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-source/avs-device-sdk/ContextManager/test
# Build directory: /home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ContextManagerTest.testSetStateForRegisteredProvider "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test/ContextManagerTest" "--gtest_filter=ContextManagerTest.testSetStateForRegisteredProvider")
add_test(ContextManagerTest.testSetStateForUnregisteredProvider "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test/ContextManagerTest" "--gtest_filter=ContextManagerTest.testSetStateForUnregisteredProvider")
add_test(ContextManagerTest.testSetStateForUnregisteredProviderWithRefreshPolicyAlways "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test/ContextManagerTest" "--gtest_filter=ContextManagerTest.testSetStateForUnregisteredProviderWithRefreshPolicyAlways")
add_test(ContextManagerTest.testGetContext "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test/ContextManagerTest" "--gtest_filter=ContextManagerTest.testGetContext")
add_test(ContextManagerTest.testMultipleGetContextRequests "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test/ContextManagerTest" "--gtest_filter=ContextManagerTest.testMultipleGetContextRequests")
add_test(ContextManagerTest.testSetProviderTwice "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test/ContextManagerTest" "--gtest_filter=ContextManagerTest.testSetProviderTwice")
add_test(ContextManagerTest.testProvideStateTimeout "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test/ContextManagerTest" "--gtest_filter=ContextManagerTest.testProvideStateTimeout")
add_test(ContextManagerTest.testRemoveProvider "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test/ContextManagerTest" "--gtest_filter=ContextManagerTest.testRemoveProvider")
add_test(ContextManagerTest.testIncorrectToken "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test/ContextManagerTest" "--gtest_filter=ContextManagerTest.testIncorrectToken")
add_test(ContextManagerTest.testEmptyProvider "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/ContextManager/test/ContextManagerTest" "--gtest_filter=ContextManagerTest.testEmptyProvider")
