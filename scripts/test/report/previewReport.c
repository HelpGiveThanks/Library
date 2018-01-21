January 15, 2018 15:50:16 Library.fmp12 - previewReport -1-
test: report: previewReport
#
#Exit field and clear preview viewing variable.
#This variable is soley there to allow admin
#users to test the print preview layout in the
#new window that is opened for it by this
#script. When it is active, the variable causes
#the preview window's script to close it when
#the user exits preview mode, and when clear,
#an admin user can exit preview mode and the
#will window will stay open. That is all this
#variable is for.
# Of course, in testing sometimes this
#variable is left active, and thus the preview
#window closes right after is opened by this
#script, so it is essential that this variable is
#cleared at the beginning of this script, so as
#not to confuse admin testers.
Go to Field [ ]
Set Variable [ $$preview ]
#
#Make sure only one preview window is open.
Close Window [ Name: "Print Preview"; Current file ]
New Window [ Name: "Print Preview"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
Go to Layout [ “PrintReportPreview” (report) ]
#
#Perform the sort show layout's headers
#and footers.
Sort Records [ Keep records in sorted order; Specified Sort Order: ruleTestReport::name; ascending
reportSubsection::name; ascending ]
[ Restore; No dialog ]
Show/Hide Toolbars
[ Lock; Show ]
#
#Go the first page.
Set Variable [ $page; Value:Get (PageNumber) ]
Enter Preview Mode
Go to Record/Request/Page [ $page ]
[ No dialog ]
#
#Tell the user why they cannot see web
#or movie media.
Show Custom Dialog [ Message: "NOTE: Only pictures in the Library or pictures linked to a file on a harddrive are printable. FileMaker
won't print web or movie files. "; Default Button: “OK”, Commit: “Yes” ]
#
#Tell the user how to close this window and
#how to go to different pages if there is more
#than one page to preview.
Show Custom Dialog [ Message: "Click the 'exit preview' button to close this window. Click the page numbers (upper left corner) to
see additional pages if there are any."; Default Button: “OK”, Commit: “Yes” ]
#
#Change menu to allow user to enter browse mode
#which makes the 'exit preview' button clickable.
#Menu also adds ability to browse records, which
#is essential for allowing user to browse pages of report.
Install Menu Set [ “HGT Preview” ]
#
#Set preview variable so when user click's the
#'exit preview' button this window will close.
Set Variable [ $$preview; Value:1 ]
#
