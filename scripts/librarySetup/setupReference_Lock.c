July 24, 2018 16:35:05 Library.fmp12 - setupReference_Lock -1-
librarySetup: setupReference_Lock
#
#
#Stop script if there are no records to lock.
If [ Get (FoundCount) = 0 ]
Exit Script [ ]
End If
#
#
#Capture the password for comparrison and to return
#the password field back to if the user fails to get the
#password right.
Set Variable [ $password; Value:librarySetupReferenceMain::password[2] ]
Set Field [ TEMP::passwordCheck; "" ]
Go to Field [ ]
#
#Use the halt instead of exit script step as the
#user can sometimes click the lock button
#twice. The halt stops the second click's
#calling up of this script.
#
#If there is a password, ask user to enter it.
If [ librarySetupReferenceMain::password[2] ≠ "" ]
Loop
Show Custom Dialog [ Message: "Enter the password to unlock — " &
 Case ( Length ( librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName ) < 36 ;
 Left ( librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName ; 35 ) & "... |" ;
 librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName & " |" ); Default
Button: “enter”, Commit: “Yes”; Button 2: “cancel”, Commit: “No”; Input #1: TEMP::passwordCheck, Password ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ TEMP::passwordCheck; "" ]
Halt Script
End If
#
#Unlock reference if password is correct.
If [ $password = TEMP::passwordCheck ]
#
#If user is in the about window,
#then take user to the unlocked about layout.
If [ Get (WindowName) = "About" ]
Go to Layout [ “setupReferenceViewUnlocked” (librarySetupReferenceMain) ]
End If
#
Show Custom Dialog [ Message: "unlocked"; Default Button: “OK”, Commit: “No” ]
Set Field [ TEMP::passwordCheck; "" ]
Set Field [ librarySetupReferenceMain::password; "" ]
Set Field [ librarySetupReferenceMain::password[2]; "" ]
#
Halt Script
End If
End Loop
#
#If there is no password, ask user to create one.
Else If [ librarySetupReferenceMain::password[2] = "" ]
Set Field [ TEMP::passwordCheck; "" ]
Show Custom Dialog [ Message: "Enter a password to lock — " &
 Case ( Length ( librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName ) < 36 ;
 Left ( librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName ; 35 ) & "... |" ;
 librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName & " |" )
 & " WARNING: If you can't remember this password, your records will remain locked."; Default Button: “enter”, Commit:
“Yes”; Button 2: “cancel”, Commit: “No”; Input #1: librarySetupReferenceMain::password, Password, "password"; Input #2:
TEMP::passwordCheck, Password, "confirm password" ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ librarySetupReferenceMain::password; "" ]
Exit Script [ ]
End If
#
#Check validity of password entered.
#
#If they don't match, ask user to try again.
Loop
If [ librarySetupReferenceMain::password ≠ TEMP::passwordCheck ]
Show Custom Dialog [ Message: "Passwords did not match."; Default Button: “enter”, Commit: “Yes”; Button 2:
“cancel”, Commit: “No”; Input #1: librarySetupReferenceMain::password, Password, "password"; Input #2: TEMP::
passwordCheck, Password, "confirm password" ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ librarySetupReferenceMain::password; "" ]
Halt Script
End If
End If
#
#If the user picks 0, then make them choose
#another and explain why the must do so.
If [ TEMP::passwordCheck = 0 ]
Show Custom Dialog [ Message: "Zero is not allowed. Try again."; Default Button: “enter”, Commit: “Yes”; Button 2:
“cancel”, Commit: “No”; Input #1: librarySetupReferenceMain::password, Password, "password"; Input #2: TEMP::
passwordCheck, Password, "confirm password" ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ librarySetupReferenceMain::password; "" ]
Halt Script
End If
End If
#
#If the password is valid exit the
#password check loop.
Exit Loop If [ librarySetupReferenceMain::password = TEMP::passwordCheck and TEMP::passwordCheck ≠ 0 ]
End Loop
#
#Move the user entered password into the
#second field, and replace it with 0, which will
#tell the system that this node is locked, but
#will not reveal to any user what the actual
#password is, as the second field appears on
#zero layouts.
Set Field [ librarySetupReferenceMain::password[2]; TEMP::passwordCheck ]
If [ TEMP::passwordCheck ≠ "" ]
Set Field [ librarySetupReferenceMain::password; 0 ]
End If
#
#If user in the Review Reference window,
#then take user to the locked review layout.
If [ Get (WindowName) = "About"
 or
Get (WindowName) = "Edit About" ]
Go to Layout [ “setupReferenceViewLocked” (librarySetupReferenceMain) ]
Set Window Title [ Current Window; New Title: "About" ]
End If
#
End If
#
Halt Script
#
