August 30, 2018 12:43:42 Library.fmp12 - libraryTypeCheckBoxRepition2 -1-
librarySetup: libraryTypeCheckBoxRepition2
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Exit the checkbox.
Go to Field [ ]
#
#Set default layout views for
#a reference library.
If [ tempSetup::InventoryLibraryYN[2] = 1 ]
Set Field [ tempSetup::layoutLtagK; "" ]
Set Field [ tempSetup::layoutRtagK; "" ]
Set Field [ tempSetup::layoutLtagN; "" ]
Set Field [ tempSetup::layoutRtagN; "" ]
#
#Designate library as a reference library.
Set Field [ TEMP::InventoryLibraryYN; "" ]
#
#Update library record.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::_Lgroup; TEMP::klibrary ]
Perform Find [ ]
Set Field [ testSubsectionGroup::orderOrLibraryType; "" ]
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
#
#Explain to user importance of sticking to the
#library type choosen once they start creating
#records for it.
Show Custom Dialog [ Message: "FYI: Records created in an inventory library, or an idea library, will cause minor problems if you
switch the library they are in to the opposite library type."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Choose the purpose for which you wish to use this library, and then don't change it (or you'll
end up fixing a lot of minor problems)."; Default Button: “OK”, Commit: “Yes” ]
#
#
#
Else
#
#
#
#Set default layout views for
#a stuff/inventory library.
Set Field [ tempSetup::layoutLtagK; "moreltagNKs2" ]
Set Field [ tempSetup::layoutRtagK; "moreReferenceMenu2SkeywordOrNode1" ]
Set Field [ tempSetup::layoutLtagN; "moreltagNKs2" ]
Set Field [ tempSetup::layoutRtagN; "moreReferenceMenu2SkeywordOrNode1" ]
#
#Designate library as a stuff/inventory library.
Set Field [ TEMP::InventoryLibraryYN; 1 ]
#
#Update library record.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::_Lgroup; TEMP::klibrary ]
Perform Find [ ]
Set Field [ testSubsectionGroup::orderOrLibraryType; 1 ]
#
#Now save a backup of the inventory reference
#records. This is due to the fact that inventory
#reference records when locked are editable
#because their is no edit layout for them. If this
#is backup is not done, then the first time going
#to the reference layout all backup fields will be
#blank, and so erase main field data, which
#would be a disaster for a user just playing
#around to see what a refernce library
#looks like in invtory mode. So to insure such an
#exploration does not result in data loss, this
#backup is done before the user can get to
#those records. Then, when they visit them,
#the backup fields will not be blank, and so,
#data in the primary fields will not be erased.
Go to Layout [ “tableReference” (reference) ]
Go to Record/Request/Page
[ First ]
Loop
#
#
#Only change records that have been changed.
#Changes result in the record modify date being
#reset, and this should only be done when the
#user modifies the record.
If [ reference::Title[1] ≠ reference::Title[2] ]
Set Field [ reference::Title[2]; reference::Title[1] ]
End If
If [ reference::thoughtsNotesEtc[1] ≠ reference::thoughtsNotesEtc[2] ]
Set Field [ reference::thoughtsNotesEtc[2]; reference::thoughtsNotesEtc[1] ]
End If
If [ reference::publicationYearOrStuffOrderNumber[1] ≠ reference::publicationYearOrStuffOrderNumber[2] ]
#
#Insure that only 3 digit numbers are
#saved in this field.
Set Variable [ $threeDigitNumber; Value:Right ( GetAsNumber (reference::publicationYearOrStuffOrderNumber[1]) ;
3 ) ]
Set Field [ reference::publicationYearOrStuffOrderNumber[2]; $threeDigitNumber ]
Set Field [ reference::publicationYearOrStuffOrderNumber; $threeDigitNumber ]
End If
#
#
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#
Go to Layout [ “defaultSetup” (aboutLibraryMain) ]
#
#Explain to user importance of sticking to the
#library type choosen once they start creating
#records for it.
Show Custom Dialog [ Message: "FYI: Records created in an inventory library, or an idea library, will cause minor problems if you
switch the library they are in to the opposite library type."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Choose the purpose for which you wish to use this library, and then don't change it (or you'll
end up fixing a lot of minor problems)."; Default Button: “OK”, Commit: “Yes” ]
End If
