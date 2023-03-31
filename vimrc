
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Vundle
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')
 
" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" Language

" Completion
Plugin 'Valloric/YouCompleteMe'

" Code display
"Plugin 'scrooloose/nerdcommenter'
Plugin 'nanotech/jellybeans.vim'
Plugin 'altercation/vim-colors-solarized'
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'yggdroot/indentline'
Plugin 'tomasr/molokai'

" Integrations
Plugin 'scrooloose/nerdtree'
Plugin 'airblade/vim-gitgutter'
Plugin 'ctrlpvim/ctrlp.vim'
Plugin 'tpope/vim-fugitive'

" Interface
Plugin 'godlygeek/tabular'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'dracula/vim'
Plugin 'morhetz/gruvbox'

" Commands
Plugin 'junegunn/fzf'
Plugin 'junegunn/fzf.vim'
"Plugin 'easymotion/vim-easymotion'

" Snippet
"Plugin 'SirVer/ultisnips'
" Snippets are separated from the engine. Add this if you want them:
"Plugin 'honza/vim-snippets'
"
"Plugin 'MarcWeber/vim-addon-mw-utils'
"Plugin 'tomtom/tlib_vim'
"Plugin 'garbas/vim-snipmate'
" Optional:
"Plugin 'honza/vim-snippets'

" syntax highlight

call vundle#end()

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Plugin
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Plugin 'scrooloose/nerdtree'
" NERDTree ON 단축키를 "\nt"로 설정
map <Leader>nt <ESC>:NERDTree<CR>

"" syntastic 설정
"set statusline+=%#warningmsg#
"set statusline+=%{SyntasticStatuslineFlag()}
"set statusline+=%*
"let g:syntastic_always_populate_loc_list = 1
"let g:syntastic_auto_loc_list = 1
"let g:syntastic_check_on_open = 1
"let g:syntastic_check_on_wq = 0
"let g:syntastic_cpp_compiler_options = ' -D_SHARED_PTR_ -std=c++17'

" Plugin 'octol/vim-cpp-enhanced-highlight'
let g:cpp_class_scope_highlight = 1
let g:cpp_member_variable_highlight = 1
let g:cpp_class_decl_highlight = 1
let g:cpp_posix_standard = 1
let g:cpp_experimental_template_highlight = 1
let g:cpp_concepts_highlight = 1

"" Plugin 'scrooloose/nerdcommenter'
"" Create default mappings
"let g:NERDCreateDefaultMappings = 1
"" Add spaces after comment delimiters by default
"let g:NERDSpaceDelims = 1
"" Use compact syntax for prettified multi-line comments
"let g:NERDCompactSexyComs = 1
"" Align line-wise comment delimiters flush left instead of following code indentation
"let g:NERDDefaultAlign = 'left'
"" Set a language to use its alternate delimiters by default
"let g:NERDAltDelims_java = 1
"" Add your own custom formats or override the defaults
"let g:NERDCustomDelimiters = { 'c': { 'left': '/**','right': '*/' } }
"" Allow commenting and inverting empty lines (useful when commenting a region)
"let g:NERDCommentEmptyLines = 1
"" Enable trimming of trailing whitespace when uncommenting
"let g:NERDTrimTrailingWhitespace = 1
"" Enable NERDCommenterToggle to check all selected lines is commented or not 
"let g:NERDToggleCheckAllLines = 1

" Trigger configuration. You need to change this to something other than <tab> if you use one of the following:
" - https://github.com/Valloric/YouCompleteMe
" - https://github.com/nvim-lua/completion-nvim
let g:UltiSnipsExpandTrigger="<tab>"
let g:UltiSnipsJumpForwardTrigger="<c-b>"
let g:UltiSnipsJumpBackwardTrigger="<c-z>"
" If you want :UltiSnipsEdit to split your window.
let g:UltiSnipsEditSplit="vertical"

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Encoding 설정
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" UTF-8
set encoding        =utf-8
set fileencodings   =utf-8,cp949,euc-kr,cp932,euc-jp,shift-jis,big5,ucs-2le,latin1
"set fileformats    =unix,dos,mac
set fileformats     =unix,dos

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 편집 기능 설정
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Tab 크기 설정
set tabstop         =4
set shiftwidth      =4
set expandtab
" 검색어 강조 기능
set hlsearch
" backup file을 만들지 않는다.
set nobackup
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 모양 설정
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Syntax highlight 기능을 사용한다.
syntax on

if has("gui_running")
" 시작 크기 설정
    set lines       =30
    set columns     =120
    set background  =dark
"    set background  =light
"
" colorscheme 설정
    colorscheme gruvbox
"    colorscheme dracula
"    colorscheme desert
"    colorscheme darkblue
"    colorscheme evening
"    colorscheme torte
"    colorscheme solarized
"    colorscheme pablo
"    colorscheme blue
"    colorscheme slate
"    colorscheme elflord
"    colorscheme molokai

" for molokai color
" https://github.com/tomasr/molokai
" If you prefer the scheme to match the original monokai background color, put this in your .vimrc file:
"let g:molokai_original = 1
" There is also an alternative scheme under development for color terminals which attempts to bring the 256 color version as close as possible to the the default (dark) GUI version. To access, add this to your .vimrc:
"let g:rehash256 = 1

" font 설정
    if has("win32")
"        set guifont    =굴림체:h9:cHANGEUL
"        set guifont    =GulimChe:h9:cHANGEUL
    elseif has("unix")
        set guifont    =D2Coding\ 10
"        set guifont    =D2Coding\ ligature\ 10
"        set guifont    =나눔고딕코딩\ 12
"        set guifont    =나눔고딕코딩\ bold\ 11
"        set guifont    =나눔고딕코딩\ bold\ 12
"        set guifont    =나눔고딕코딩\ 12
"        set guifont    =Noto\ Mono\ CJK\ KR\ Regular\ 10
"        set guifont    =Noto\ Sans\ Mono\ CJK\ KR\ Regular\ 10
"        set guifont    =IBM\ Plex\ Mono\ Regular\ 10
"        set guifont    =Hack\ Regular\ 10
"        set guifont    =Cascadia\ Code\ Regular\ 10
"        set guifont    =Cascadia\ Mono\ Regular\ 10
"        set guifont    =monospace\ 8
"        set guifont    =terminus\ 8
"        set guifont    =Consolas\ 8
"        set guifont    =Liberation\ Monospace\ 8
"        set guifontwide=렉시굴림\ 8
"        set guifontwide=돋움체\ 8
"        set guifontwide=네이버사전\ 8
"        set guifontwide=나눔고딕\ 8
"        set guifontwide=다음\ 8
"        set guifontwide=조선일보명조\ 8
"        set guifontwide=D2Coding\ bold\ 12
    endif
"    set guifont    =Jung9\ 9
"    set guifont    =Fixedsys:h12:cHANGEUL
else
    set background    =dark
endif
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Syntax highlight와 들여쓰기
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 파일의 종류를 자동으로 인식
filetype plugin indent on
" 자동 들여쓰기
set autoindent

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Syntax highlight와 들여쓰기
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" ctags
" https://rderik.com/blog/ctags-vim-multiple-projects/
"set tags=./tags,/media/PROJECT02/project/RailAdvisor5/tags

