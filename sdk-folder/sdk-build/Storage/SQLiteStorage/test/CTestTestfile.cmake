# CMake generated Testfile for 
# Source directory: /home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-source/avs-device-sdk/Storage/SQLiteStorage/test
# Build directory: /home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SQLiteDatabaseTest.CloseThenOpen "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.CloseThenOpen" ".")
add_test(SQLiteDatabaseTest.InitializeAlreadyExisting "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.InitializeAlreadyExisting" ".")
add_test(SQLiteDatabaseTest.InitializeBadPath "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.InitializeBadPath" ".")
add_test(SQLiteDatabaseTest.InitializeOnDirectory "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.InitializeOnDirectory" ".")
add_test(SQLiteDatabaseTest.InitializeTwice "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.InitializeTwice" ".")
add_test(SQLiteDatabaseTest.OpenAlreadyExisting "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.OpenAlreadyExisting" ".")
add_test(SQLiteDatabaseTest.OpenBadPath "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.OpenBadPath" ".")
add_test(SQLiteDatabaseTest.OpenDirectory "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.OpenDirectory" ".")
add_test(SQLiteDatabaseTest.OpenTwice "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.OpenTwice" ".")
add_test(SQLiteDatabaseTest.TransactionsCommit "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.TransactionsCommit" ".")
add_test(SQLiteDatabaseTest.TransactionsRollback "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.TransactionsRollback" ".")
add_test(SQLiteDatabaseTest.NestedTransactions "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.NestedTransactions" ".")
add_test(SQLiteDatabaseTest.DoubleCommit "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.DoubleCommit" ".")
add_test(SQLiteDatabaseTest.AutoRollback "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteDatabaseTest" "--gtest_filter=SQLiteDatabaseTest.AutoRollback" ".")
add_test(SQLiteMiscStorageTest.createStringKeyValueTable "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteMiscStorageTest" "--gtest_filter=SQLiteMiscStorageTest.createStringKeyValueTable" ".")
add_test(SQLiteMiscStorageTest.tableEntryTests "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteMiscStorageTest" "--gtest_filter=SQLiteMiscStorageTest.tableEntryTests" ".")
add_test(SQLiteMiscStorageTest.loadAndClear "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteMiscStorageTest" "--gtest_filter=SQLiteMiscStorageTest.loadAndClear" ".")
add_test(SQLiteMiscStorageTest.createDeleteTable "/home/junlon2006/workspace/amazon/avs_2rd/sdk-folder/sdk-build/Storage/SQLiteStorage/test/SQLiteMiscStorageTest" "--gtest_filter=SQLiteMiscStorageTest.createDeleteTable" ".")
