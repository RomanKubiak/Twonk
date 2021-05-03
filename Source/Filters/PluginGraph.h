#pragma once

#include "../UI/PluginWindow.h"
class TwonkPlayHead;
class Document;
//==============================================================================
/**
    A collection of plugins and some connections between them.
*/
class PluginGraph   : public FileBasedDocument,
                      public AudioProcessorListener,
                      private ChangeListener
{
public:
    PluginGraph (AudioPluginFormatManager &fm, Document &_documentOwner, TwonkPlayHead &_twonkPlayHead);
    ~PluginGraph() override;
    using NodeID = AudioProcessorGraph::NodeID;
    void addPlugin (const PluginDescription&, Point<double>);
    AudioProcessorGraph::Node::Ptr getNodeForName (const String& name) const;
    void setNodePosition (NodeID, Point<double>);
    Point<double> getNodePosition (NodeID) const;
    void clear();
    PluginWindow* getOrCreateWindowFor (AudioProcessorGraph::Node*, PluginWindow::Type);
    void closeCurrentlyOpenWindowsFor (AudioProcessorGraph::NodeID);
    bool closeAnyOpenPluginWindows();
    void audioProcessorParameterChanged (AudioProcessor*, int, float) override {}
    void audioProcessorChanged (AudioProcessor* processor, const ChangeDetails& details) { changed(); }
    std::unique_ptr<XmlElement> createXml() const;
    void restoreFromXml (const XmlElement&);
    static const char* getFilenameSuffix()      { return ".twonk"; }
    static const char* getFilenameWildcard()    { return "*.twonk"; }
    void newDocument();
    String getDocumentTitle() override;
    Result loadDocument (const File& file) override;
    Result saveDocument (const File& file) override;
	File getSuggestedSaveAsFile (const File &defaultFile) override;
    File getLastDocumentOpened() override;
    void setLastDocumentOpened (const File& file) override;
    static File getDefaultGraphDocumentOnMobile();
    Document &getDocumentOwner() { return (documentOwner); }
    AudioProcessorGraph graph;

private:
	Document &documentOwner;
    AudioPluginFormatManager& formatManager;
    OwnedArray<PluginWindow> activePluginWindows;
	TwonkPlayHead &twonkPlayHead;
    NodeID lastUID;
    NodeID getNextUID() noexcept;

    void createNodeFromXml (const XmlElement&);
    void addPluginCallback (std::unique_ptr<AudioPluginInstance>, const String& error, Point<double>);
    void changeListenerCallback (ChangeBroadcaster*) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginGraph)
};
