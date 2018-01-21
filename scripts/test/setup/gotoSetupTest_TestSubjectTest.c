January 11, 2018 20:16:53 Library.fmp12 - gotoSetupTest_TestSubjectTest -1-
test: setup: gotoSetupTest_TestSubjectTest
#
#
#If the PRIMARY node is currenlty locked then
#stop this script, and inform the user.
If [ TEMP::primaryNodeIsLocked ≠ "" ]
Show Custom Dialog [ Message: "The default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is locked. Go to
the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary node, or C) create a
new primary node."; Default Button: “OK”, Commit: “No” ]
Exit Script [ ]
End If
#
Go to Layout [ “defaultTestNewSection” (testSectionCreatedFromATemplate) ]
#
