# CMake generated Testfile for 
# Source directory: /home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-source/avs-device-sdk/CapabilitiesDelegate/test
# Build directory: /home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilitiesDelegate/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(CapabilitiesDelegateTest.noCapability "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilitiesDelegate/test/CapabilitiesDelegateTest" "--gtest_filter=CapabilitiesDelegateTest.noCapability")
add_test(CapabilitiesDelegateTest.withCapabilitiesHappyCase "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilitiesDelegate/test/CapabilitiesDelegateTest" "--gtest_filter=CapabilitiesDelegateTest.withCapabilitiesHappyCase")
add_test(CapabilitiesDelegateTest.publishFatalError "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilitiesDelegate/test/CapabilitiesDelegateTest" "--gtest_filter=CapabilitiesDelegateTest.publishFatalError")
add_test(CapabilitiesDelegateTest.publishRetriableError "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilitiesDelegate/test/CapabilitiesDelegateTest" "--gtest_filter=CapabilitiesDelegateTest.publishRetriableError")
add_test(CapabilitiesDelegateTest.republish "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilitiesDelegate/test/CapabilitiesDelegateTest" "--gtest_filter=CapabilitiesDelegateTest.republish")
add_test(CapabilitiesDelegateTest.registerTests "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilitiesDelegate/test/CapabilitiesDelegateTest" "--gtest_filter=CapabilitiesDelegateTest.registerTests")
add_test(CapabilitiesDelegateTest.testClearData "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/CapabilitiesDelegate/test/CapabilitiesDelegateTest" "--gtest_filter=CapabilitiesDelegateTest.testClearData")
subdirs(Common)
