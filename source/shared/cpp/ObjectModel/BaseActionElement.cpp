#include "pch.h"
#include "BaseActionElement.h"
#include "BaseElement.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

BaseActionElement::BaseActionElement(ActionType type) :
    m_type(type), m_sentiment(Sentiment::Default)
{
    SetTypeString(ActionTypeToString(type));
    PopulateKnownPropertiesSet();
}


std::string BaseActionElement::GetTitle() const
{
    return m_title;
}

void BaseActionElement::SetTitle(const std::string& value)
{
    m_title = value;
}

std::string BaseActionElement::GetIconUrl() const
{
    return m_iconUrl;
}

void BaseActionElement::SetIconUrl(const std::string& value)
{
    m_iconUrl = value;
}

Sentiment BaseActionElement::GetSentiment() const
{
    return m_sentiment;
}

void BaseActionElement::SetSentiment(const Sentiment& value)
{
    m_sentiment = value;
}

const ActionType BaseActionElement::GetElementType() const
{
    return m_type;
}

Json::Value BaseActionElement::SerializeToJsonValue() const
{
    Json::Value root = BaseElement::SerializeToJsonValue();

    if (!m_iconUrl.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IconUrl)] = m_iconUrl;
    }

    if (!m_title.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = m_title;
    }

    if (m_sentiment != Sentiment::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Sentiment)] = SentimentToString(m_sentiment);
    }

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = ActionTypeToString(m_type);

    //SerializeFallbackAndRequires(root);

    return root;
}

void BaseActionElement::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Fallback),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IconUrl),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Requires),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Sentiment),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)});
}

void BaseActionElement::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    if (!m_iconUrl.empty())
    {
        RemoteResourceInformation imageResourceInfo;
        imageResourceInfo.url = m_iconUrl;
        imageResourceInfo.mimeType = "image";
        resourceInfo.push_back(imageResourceInfo);
    }
}

void BaseActionElement::ParseJsonObject(ParseContext& context, const Json::Value& json, std::shared_ptr<BaseElement>& baseElement)
{
    baseElement = ParseUtil::GetActionFromJsonValue(context, json);
}
