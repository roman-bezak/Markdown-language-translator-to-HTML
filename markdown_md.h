#ifndef MARKDOWN_H_INCLUDED
#define MARKDOWN_H_INCLUDED

#include <iostream>
#include <string>
#include <list>

#include <boost\noncopyable.hpp>
#include <boost\shared_ptr.hpp>
#include <boost\optional.hpp>
#include <boost\unordered_map.hpp>

namespace markdown {

	using boost::optional;
	using boost::none;


	class Token;
	class LinkIds;

	typedef boost::shared_ptr<Token> TokenPtr;
	typedef std::list<TokenPtr> TokenGroup;

	class Document: private boost::noncopyable {
		public:
		Document(size_t spacesPerTab=cDefaultSpacesPerTab);
		Document(std::istream& in, size_t spacesPerTab=cDefaultSpacesPerTab);
		~Document();


		bool read(const std::string&);
		bool read(std::istream&);
		void write(std::ostream&);
		void writeTokens(std::ostream&);


		Document copy() const;

		private:
		bool _getline(std::istream& in, std::string& line);
		void _process();
		void _mergeMultilineHtmlTags();
		void _processInlineHtmlAndReferences();
		void _processBlocksItems(TokenPtr inTokenContainer);
		void _processParagraphLines(TokenPtr inTokenContainer);

		static const size_t cSpacesPerInitialTab, cDefaultSpacesPerTab;

		const size_t cSpacesPerTab;
		TokenPtr mTokenContainer;
		LinkIds *mIdTable;
		bool mProcessed;
	};

} // namespace markdown

#endif // MARKDOWN_H_INCLUDED
