January 10, 2018 16:04:02 Library.fmp12 - newLibraryStep1_CreateACopyOfThisLibraryFile -1-
libraryNewOrImport: newLibraryStep1_CreateACopyOfThisLibraryFile
#
#
#PURPOSE: This script is step 1 of a three step
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
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#
#BEGIN STEP 1: Create a copy of this library.
#
#Make sure the admin user wants to create
#a new library file.
Show Custom Dialog [ Message: "Create a newlibrary?"; Default Button: “OK”, Commit: “No”; Button 2: “cancel”, Commit: “No” ]
#
#If admin user clicks cancel then exit
#this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#Set code for library erasure, so when opened,
#the copy of this library will read this code and
#begin the process of erasing all data in
#the copy.
Go to Layout [ “backup” (backup) ]
Delete All Records
[ No dialog ]
New Record/Request
Set Field [ backup::newLibrary; "234874920347574weidf792342f9823984" ]
#
#Go to main library layout to give user a nice
#background against which to show the
#dialogue boxes.
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
#
#Ask user to create the necessary folders for
#the new library file's files.
Show Custom Dialog [ Message: "Create a folder for this new library in your library folder. Then create another new folder, in that
folder, and name it 'x'. DO THIS NOW."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
#If admin user clicks cancel then exit
#this script.
If [ Get ( LastMessageChoice ) = 2 ]
Go to Layout [ “backup” (backup) ]
Set Field [ backup::newLibrary; "" ]
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
Exit Script [ ]
End If
#
#Tell the user to put the copy of this library
#file into the newly created folder.
Show Custom Dialog [ Message: "When asked next where to put your new library, select the new library folder that you just created
(with the empty folder named 'x' inside it)."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
#If admin user clicks cancel then exit
#this script.
If [ Get ( LastMessageChoice ) = 2 ]
Go to Layout [ “backup” (backup) ]
Set Field [ backup::newLibrary; "" ]
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
Exit Script [ ]
End If
#
#Create a copy of this library file.
Save a Copy as [ ]
[ copy of current file ]
#
#If admin user clicks cancel then exit
#this script.
If [ Get ( LastError ) = 1 ]
Go to Layout [ “backup” (backup) ]
Set Field [ backup::newLibrary; "" ]
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
Exit Script [ ]
End If
#
#To insure that this orginal flie does not get
#erased when started, remove the erase code.
Go to Layout [ “backup” (backup) ]
Set Field [ backup::newLibrary; "" ]
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
#
#Close this file and inform user to now open
#their copy of this library just created and set
#it up = erase its records.
Show Custom Dialog [ Message: "This library will now close. Go to your new library's folder. Name your new library file. Double click
it to start it up. Allow it to delete its files, which are duplicates of this library's files."; Default Button: “OK”, Commit: “Yes” ]
#
#Close all open windows, which will
#close this library.
Perform Script [ “closeLibrary” ]
#
#END STEP 1: Create a copy of this library.
#
#
