January 18, 2018 15:41:45 Library.fmp12 - showTagLink2 -1-
reference: showTagLink2
#
#Capture needed link info.
Set Variable [ $$tagMenusRealCheckbox; Value:tagFileLocation2::kfileORkTestItemCreatorNode ]
Set Variable [ $$tagMenusFilePath; Value:tagFileLocation2::tag ]
Set Variable [ $$tagMenusFileName; Value:refTitle2::fileName ]
Set Variable [ $$tagMenusFileLocation; Value:refTitle2::kfileLocation ]
Set Variable [ $$tagMenusURL; Value:refTitle2::URL ]
Set Variable [ $$tagMenusISBN; Value:refTitle2::ISBN ]
Set Variable [ $$tagMenusISSN; Value:refTitle2::ISSN ]
Set Variable [ $$tagMenusDOI; Value:refTitle2::DOI ]
#
#Open link for user.
Perform Script [ “showReferencedFileFolderOrWebsite (update and name showFileInTagandLearnWindows)” ]
#
#Clear link variables.
Set Variable [ $$tagMenusRealCheckbox ]
Set Variable [ $$tagMenusFilePath ]
Set Variable [ $$tagMenusFileName ]
Set Variable [ $$tagMenusFileLocation ]
Set Variable [ $$tagMenusURL ]
Set Variable [ $$tagMenusISBN ]
Set Variable [ $$tagMenusISSN ]
Set Variable [ $$tagMenusDOI ]
#
