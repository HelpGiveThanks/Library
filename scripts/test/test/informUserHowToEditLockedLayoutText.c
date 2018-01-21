January 15, 2018 14:48:56 Library.fmp12 - informUserHowToEditLockedLayoutText -1-
test: test: informUserHowToEditLockedLayoutText
#
#Inform user how to edit a test item if the try
#to edit one while in the testing or report
#section. This is not allowed, so when the
#user does edit an item they see the copyright
#for the item, which is only displayed in the
#edit section.
Allow User Abort [ Off ]
Set Error Capture [ On ]
If [ Get ( LayoutTableName ) = "tagMenus" and $$citationMatch ≠ "copyright" and $$showCopyrightLockMessage = "" ]
Show Custom Dialog [ Message: "To edit a test item, click the 'edit/new' button. Selecting and copying item text is allowed.";
Default Button: “OK”, Commit: “Yes” ]
Else If [ $$citationMatch = "copyright" and tagCreatorLock::orderOrLock ≠ ""
or
$$showCopyrightLockMessage = 1 and tagCreatorLock::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This copyright was copy, pasted, and locked by " & tagCreatorLock::tag & ". Selecting and
copying its text is allowed. Click the 'web' button to see the original. To unlock it, go the default node menu and enter the
password for " & tagCreatorLock::tag & "."; Default Button: “OK”, Commit: “Yes” ]
Else If [ $$citationMatch = "copyright" and tagMenus::orderOrLock = "lock"
or
$$showCopyrightLockMessage = 1 and tagMenus::orderOrLock = "lock" ]
Show Custom Dialog [ Message: "This is a Library " & TEMP::versionNumber & " copy of a copyright and cannot be changed.
Selecting and copying its text is allowed. Click the 'web' button to see the original."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "To edit test information, click 'back' and then click" & ¶ & "the 'edit/new' button. Selecting and
copying text is allowed."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#The halt script step stops FileMaker from
#displaying its own error message.
Halt Script
#
