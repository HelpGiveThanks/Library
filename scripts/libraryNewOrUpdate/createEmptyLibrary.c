January 10, 2018 16:12:10 Library.fmp12 - newLibraryStep2eraseRecordsInCopyOfLibrary -1-
libraryNewOrImport: newLibraryStep2eraseRecordsInCopyOfLibrary
#
#
#PURPOSE: This script is step 2 of a three step
#process for creating a copy of the current
#library file for use as a new empty library or
#as an upgrade library file.
#— Admin access required. —
# Step 1) Creates a copy of current library.
#A copy not a clone must be created because some
#records are neccessary to running the Library and
#are removed when cloning the Library.
#— Admin access required. —
# Step 2) When user opens the copy that this
#script creates, the createEmptyLibrary script
#erases the copy's records preparing it to
#become an empty library or an upgrade file
#of the library ready for sharing.
#— Regular user access —
# Step 3 A) Create new library name
#and node records and begin to use the library
#file as a new library, OR B) Import records
#from an older library and use library file as an
#upgrade library file.
#
#
#BEGIN STEP 2: Erase library copy's records.
#
#Admin tasks.
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
#If this is an old library full of data, then
#prepare to erase it and turn it into a new/
#empty library. This will be true when an
#admin user triggers this script from the
#script menu.
// If [ backup::newLibrary = "234874920347574weidf792342f9823984" ]
#
#Go the library's main layout and insure that
#their is only on record to show.
Go to Layout [ “defaultsAll” (tempSetup) ]
Show All Records
Delete All Records
[ No dialog ]
New Record/Request
#
#In the past errors occurred where the orginal
#library file crashed before the above erase
#library variable could be removed. This
#dialogue box allows the admin user to
#remove this erase variable from the current
#libary by clicking stop. Once, the libary can
#be opened and will function normally. If the
#admin user really wanted to erase the this
#library's data, they will have to start the
#create-new-library process all over again.
Show Custom Dialog [ Message: "Are you sure you want to delete the data in " & tempSetup::fileNameOnALLDefaultsLayout &
" to make it a new empty one? If you are not sure, DO NOT CLICK any of the buttons. Instead, check the folder where this
library is located and make sure this is a copy of the orignal and not the original. Next click either the stop or proceed button.";
Default Button: “stop”, Commit: “Yes”; Button 2: “proceed”, Commit: “No” ]
#
#If the admin user clicks stop then remove the
#erase variable turning this library into a
#normal library with all its data intact.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Layout [ “backup” (backup) ]
Set Field [ backup::newLibrary; "" ]
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
Exit Script [ ]
End If
#
#If user clicks proceed then continue with
#step 2 and erase this library's data.
#
#Clear all temp records fields, which hold data
#from the records that will be deleted next.
Go to Layout [ “tableTemp” (TEMP) ]
New Record/Request
Go to Field [ TEMP::addTestItemGroup ]
Loop
Set Field [ "" ]
Go to Next Field
Exit Loop If [ Get ( ActiveFieldName ) = "addTestItemGroup" ]
End Loop
#
#
#1) Delete test section records.
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Show All Records
Delete All Records
[ No dialog ]
#
#
#2) Delete test subsection records.
Go to Layout [ “tableTestSubsectionTemplates” (testSubsectionTemplate) ]
Show All Records
Delete All Records
[ No dialog ]
#
#
#3) Delete learn and test result records.
Go to Layout [ “tableTestLearn” (testlearn) ]
Show All Records
Delete All Records
[ No dialog ]
#
#
#4) Delete LIBRARY SETUP reference records.
Go to Layout [ “tableSetupReference” (setupReference) ]
Show All Records
Delete All Records
[ No dialog ]
#
#
#5) Delete tag records.
Go to Layout [ “tableTag” (tagTable) ]
Show All Records
Delete All Records
[ No dialog ]
#
#
#6) Delete tag group records.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Show All Records
Delete All Records
[ No dialog ]
#
#
#7) Delete reference records.
Go to Layout [ “tableReference” (reference) ]
#
#Remove reference records containing
#copyright symbol images and links used
#by the default copyright tag records.
Enter Find Mode [ ]
Set Field [ reference::lock; "lock" ]
Perform Find [ ]
Show Omitted Only
Delete All Records
[ No dialog ]
#
#
#8) Delete report records.
Go to Layout [ “tableReport” (report) ]
Show All Records
Delete All Records
[ No dialog ]
#
#
#Note that this a fresh library ready to be
#used as a new library or to accept the data
#from an old library (as is the case when
#upgrading from an old to a new version of
#the Library).
Go to Layout [ “backup” (backup) ]
Set Field [ backup::newLibrary; "newLibrary" ]
#
#Go to the default main layout for the final
#script steps.
Go to Layout [ “defaultsAll” (tempSetup) ]
#
#Make sure to clear the library type field else
#user may see both idea and thing library
#checkboxes checked for this library file.
Set Field [ tempSetup::InventoryLibraryYN; "" ]
Set Field [ tempSetup::InventoryLibraryYN[2]; "" ]
#
#Close this library and instruct user to
#restart it. (Due to import failures/crashes
#during import it is essential to create
#mutliple copies of a new library file before
#attempting to import an old library into it.)
Show Custom Dialog [ Message: "This library is now ready for use. It will close. When users next open it they will be asked if
they want to use it as a new library or import records from an old Library file into it."; Default Button: “OK”, Commit: “Yes” ]
Perform Script [ “closeLibrary (update)” ]
#
// End If
#
#END STEP 2: Erase library copy's records.
#
#
