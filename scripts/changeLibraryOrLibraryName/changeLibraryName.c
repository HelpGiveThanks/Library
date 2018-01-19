January 11, 2018 19:18:24 Library.fmp12 - changeLibraryName -1-
librarySetup: changeLibraryName
#
#Update the temp library name field and the
#library's backup spelling field (not is use at
#this time because I decided the library's name
#should not be lockable, so if remixed, the
#shared remix can have a new name to not
#confuse it with the original, which may be
#composed of locked records).
#
#Save and capture new library name and
#version number once the user leaves
#either the field.
Commit Records/Requests
Set Variable [ $name; Value:tempSetup::userLibraryName ]
Set Variable [ $version; Value:tempSetup::userLibraryVersionNumber ]
#
#Update library record.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::_Lgroup; TEMP::klibrary ]
Perform Find [ ]
Set Field [ testSubsectionGroup::name; $name ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $name ]
If [ $version ≠ "" ]
Set Field [ testSubsectionGroup::versionNumber; $version ]
Else
Set Field [ testSubsectionGroup::versionNumber; "" ]
End If
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
#
#Make sure users understand that this field is
#for this copy only, whereas the library setup
#reference records travel with each copy.
Show Custom Dialog [ Message: "The name and version fields are for you to customize your copy of this library file. If you plan on
publishing it for others to use, create a library setup reference record below. Click the ? button for more info."; Default Button:
“OK”, Commit: “Yes” ]
#
#
