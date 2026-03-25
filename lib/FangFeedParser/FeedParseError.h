#ifndef FEEDPARSEERROR_H
#define FEEDPARSEERROR_H

enum class FeedParseError {
    None,
    EmptyInput,
    MalformedXML,
    MalformedJSON,
    UnrecognizedFormat,
    MissingRequiredFields
};

#endif // FEEDPARSEERROR_H
