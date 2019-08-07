#include "../JuceLibraryCode/JuceHeader.h"

#ifndef MRALIASPRO
static const String encryptXml (const XmlElement* xml,
                                const String& rsaPrivateKey)
{
    BigInteger val;

    if (xml != 0)
    {
        const String s (xml->createDocument ("", true));
		const MemoryBlock mb (s.toUTF8(), s.length());

        val.loadFromMemoryBlock (mb);
    }

    RSAKey key (rsaPrivateKey);
    key.applyToValue (val);

    return val.toString (16);
}
#endif

static XmlElement* decodeEncryptedXml (const String& hexData,
                                       const String& rsaPublicKey)
{
    if (hexData.isEmpty())
        return 0;

    BigInteger val;
    val.parseString (hexData, 16);

    RSAKey key (rsaPublicKey);
    key.applyToValue (val);

    const MemoryBlock mb (val.toMemoryBlock());
    XmlDocument doc (mb.toString());

    XmlElement* const xml = doc.getDocumentElement().get();

#ifdef JUCE_DEBUG
    if (xml != 0)
    {
        DBG (xml->createDocument ("", true));
    }
#endif

    return xml;
}
