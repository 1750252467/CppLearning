# markdown文档自动生成目录

## 安装doctoc教程（ubtoun18.04）

### 相关依赖升级或安装一下(按序执行)

```shell
sudo apt install libssl1.0-dev
sudo apt install nodejs-dev
sudo apt install node-gyp
sudo apt install npm
npm install -g doctoc
```



## 安装后doctoc命令找不到解决办法

### 可能是nodejs的依赖问题

```bash
curl -sL https://deb.nodesource.com/setup_14.x | sudo -E bash -
sudo apt-get install -y nodejs
```

安装node时，一直报错，解决办法

将`etc/apt/sources.list.d`文件先全部备份

```bash
sudo mv etc/apt/sources.list.d etc/apt/sources.list.d.bak
```

然后新建`etc/apt/sources.list.d`文件夹，里面新建`nodesource.list`文件

文件内写入：

```bash
deb [signed-by=/usr/share/keyrings/nodesource.gpg] https://deb.nodesource.com/node_14.x bionic main
```

然后再执行`curl`命令

![请添加图片描述](https://img-blog.csdnimg.cn/08edacdf0da34908ae0720b41c894038.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAbW9uZXlteW9uZQ==,size_20,color_FFFFFF,t_70,g_se,x_16)

提示[安装nodejs](https://so.csdn.net/so/search?q=安装nodejs&spm=1001.2101.3001.7020),再安装即可

### 安装nodejs

```bash
sudo apt-get install -y nodejs
1
```

### 查看安装版本

```bash
npm -v
node -v
nodejs -v //这个命令可能找不到,但上述步骤完成后依赖更新，doctoc命令就可以用了

qiancj@qianchengjun:~$ npm -v
6.14.16
qiancj@qianchengjun:~$ node -v
v14.19.1
qiancj@qianchengjun:~$ nodejs -v
v14.19.1
```

## 用法

在最简单的用法中，您可以将一个或多个文件或文件夹传递给命令。这将更新每个指定文件的目录以及 通过递归搜索每个文件夹找到每个 Markdown 文件。以下是一些 例子。`doctoc`

### 将目录添加到目录和子目录中的所有文件

进入包含本地 git 项目的目录并键入：

```
doctoc .
```

这将更新当前目录中的所有降价文件及其所有 具有指向生成的锚点的内容目录的子目录 通过降价解析器。Doctoc 默认使用 GitHub 解析器，但其他[模式可以是 指定](https://www.npmjs.com/package/doctoc?activeTab=readme#using-doctoc-to-generate-links-compatible-with-other-sites)。

### 忽略单个文件

为了在整个目录上运行时忽略特定文件，只需添加到要忽略的文件的顶部即可。`doctoc``<!-- DOCTOC SKIP -->`

### 轻松更新现有的文档目录

如果您已经通过doctoc插入了目录，它将通过运行命令自动更新（而不是插入重复的目录）。Doctoc 通过 和 注释定位目录，因此您还可以将生成的目录移动到文档的任何其他部分，它将在那里更新。`<!-- START doctoc -->``<!-- END doctoc -->`

### 将目录添加到单个文件

如果只想转换特定文件，请执行以下操作：

```
doctoc /path/to/file [...]
```

#### 例子

```
doctoc README.md

doctoc CONTRIBUTING.md LICENSE.md
```

### 使用doctoc生成与其他网站兼容的链接

为了添加其链接兼容的目录，其他站点添加适当的模式标志：

可用模式包括：

```
--bitbucket bitbucket.org
--nodejs    nodejs.org
--github    github.com
--gitlab    gitlab.com
--ghost     ghost.org
```

#### 例

```
doctoc README.md --bitbucket
```

### 指定目录的位置

默认情况下，doctoc 将目录放在文件的顶部。您可以指示将其放置在其他位置，格式如下：

```
<!-- START doctoc -->
<!-- END doctoc -->
```

将此代码直接放在 .md 文件中。例如：

```
// my_new_post.md
Here we are, introducing the post. It's going to be great!
But first: a TOC for easy reference.

<!-- START doctoc -->
<!-- END doctoc -->

# Section One

Here we'll discuss...
```

运行文档将在该位置插入目录。

### 指定自定义目录标题

使用该选项指定（降价格式）自定义目录标题;例如，从那时起，您可以简单地运行，doctoc 将保留您指定的标题。`--title``doctoc --title '**Contents**' .``doctoc <file>`

或者，要清空标题，请使用该选项。这将简单地从目录中删除标题。`--notitle`

### 指定目录条目的最大标题级别

使用该选项将目录条目限制为仅指定级别的标题;例如，`--maxlevel``doctoc --maxlevel 3 .`

默认情况下，

- 对降价格式的标题没有限制，
- 而嵌入式 HTML 的标题仅限于 4 个级别。

### 打印到标准输出

您可以使用 or 选项打印到标准输出。`-s``--stdout`

### 仅更新现有目录

使用 or 仅更新现有目录。也就是说，没有 ToC 的 Markdown 文件将保持不变。如果要与 一起使用，那就太好了。`--update-only``-u``doctoc``lint-staged`

### 用作钩子`git`

doctoc 可以用作[预提交](http://pre-commit.com/)钩子，方法是使用 以下配置：

```
repos:
-   repo: https://github.com/thlorenz/doctoc
    rev: ...  # substitute a tagged version
    hooks:
    -   id: doctoc
```

这将在提交时针对 markdown 文件运行，以确保 目录保持最新。`doctoc`