July 20, 2018 17:25:19 Library.fmp12 - newLibraryStep3A_makeEmptiedLibraryANewLibrary -1-
libraryNewOrImport: newLibraryStep3A_makeEmptiedLibraryANewLibrary
#
#
#PURPOSE: This script is step 3A of a three step
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
#BEGIN STEP 3A: Create new library records.
#
#1) Create a node group. Do this first as its ID
#is needed for both the primary node that
#needs to be created and the library name
#and info record.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
New Record/Request
Set Field [ testSubsectionGroup::match; "node" ]
Set Field [ testSubsectionGroup::orderOrLibraryType; "001" ]
Set Field [ testSubsectionGroup::name; "record creators and test subjects" ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; "record creators and test subjects" ]
Commit Records/Requests
[ Skip data entry validation; No dialog ]
Set Variable [ $group; Value:testSubsectionGroup::_Lgroup ]
Set Variable [ $groupName; Value:testSubsectionGroup::name ]
#
#2) Create the library name and info record,
#and add group ID and name to it.
New Record/Request
Set Field [ testSubsectionGroup::orderOrLibraryType; $group ]
Set Field [ testSubsectionGroup::nameSpellingFORTestItemGroup; $groupName ]
Set Field [ testSubsectionGroup::match; "library" ]
Set Field [ testSubsectionGroup::name; "New Library" ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; "New Library" ]
Set Field [ testSubsectionGroup::versionNumber; "" ]
Commit Records/Requests
[ Skip data entry validation; No dialog ]
#
#3) Create the library's first node, and assign
#it to the library's first group, and make it the
#primary/author node for new library records.
Go to Layout [ “tableTag” (tagTable) ]
New Record/Request
Set Field [ tagTable::match; "node" ]
Set Field [ tagTable::kGroupOrTest; $group ]
Set Field [ tagTable::tag; "LastName, FirstName" ]
Set Field [ tagTable::tagSpelling; "LastName, FirstName" ]
#
#In Setup section only show creator nodes,
#as these are the only nodes that can create
#or edit library records.
Set Field [ tagTable::textStyleOrCreatorNodeFlag; 123456789 ]
Commit Records/Requests
[ Skip data entry validation; No dialog ]
#
#Now set node variables.
Set Variable [ $node; Value:tagTable::_Ltag ]
Set Variable [ $nodeName; Value:tagTable::tag ]
Set Field [ tagTable::kRecordCreatorNode; $node ]
Set Field [ TEMP::kdefaultNodePrimary; $node ]
Set Field [ TEMP::DEFAULTNodePrimaryName; $nodeName ]
#
#4) Make the new node the creator of the
#first node group, and the library too.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Perform Find [ Specified Find Requests: Find Records; Criteria: testSubsectionGroup::match: “"node"” ]
[ Restore ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; $node ]
Perform Find [ Specified Find Requests: Find Records; Criteria: testSubsectionGroup::match: “"library"” ]
[ Restore ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; $node ]
Set Field [ testSubsectionGroup::ReportCaptionORLibraryCreatorName; $nodeName ]
#
#
#Erase codes that trigger new
#library creation script steps.
Go to Layout [ “backup” (backup) ]
Delete All Records
[ No dialog ]
New Record/Request
Set Field [ backup::backup; "" ]
Set Field [ backup::newLibrary; "" ]
#
#Complete new library by restarting it, loading
#up the newly created data, telling the user
#to change the primary node's name, select
#the copyright for new records, and
#change the name of library X.
# This variable will trigger these final steps
#found at the end of startDatabase script.
Set Variable [ $$newLibraryNextSteps; Value:1 ]
Perform Script [ “startDatabase” ]
#
#END STEP 3A: Create new library records.
#
#
