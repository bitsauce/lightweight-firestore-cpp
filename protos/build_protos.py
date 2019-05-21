#! /usr/bin/env python

# Copyright 2018 Google
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from __future__ import print_function

# Run the following command in this directory to re-generate protos/cpp files:
"""
python build_protos.py `
 	--protos_dir protos/ `
 	--output_dir ./ `
 	--protoc $env:VCPKG_ROOT/installed/x64-windows-v140/tools/protobuf/protoc.exe `
    --grpc_cpp_plugin $env:VCPKG_ROOT/installed/x64-windows-v140/tools/grpc/grpc_cpp_plugin.exe `
 	-I protos/ `
 	-I $env:VCPKG_ROOT/installed/x64-windows-v140/include
"""

"""Generates and massages protocol buffer outputs.
"""


import sys

import argparse
import os
import os.path
import re
import subprocess


CPP_GENERATOR = 'nanopb_cpp_generator.py'


COPYRIGHT_NOTICE = '''
/*
 * Copyright 2018 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
'''.lstrip()


def main():
	parser = argparse.ArgumentParser(
			description='Generates proto messages.')
	parser.add_argument(
			'--protos_dir',
			help='Source directory containing .proto files.')
	parser.add_argument(
			'--output_dir', '-d',
			help='Directory to write files; subdirectories will be created.')
	parser.add_argument(
			'--protoc', default='protoc',
			help='Location of the protoc executable')
	parser.add_argument(
			'--grpc_cpp_plugin', default='grpc_cpp_plugin',
			help='Location of the grpc_cpp_plugin executable')
	parser.add_argument(
			'--pythonpath',
			help='Location of the protoc python library.')
	parser.add_argument(
			'--include', '-I', action='append', default=[],
			help='Adds INCLUDE to the proto path.')

	args = parser.parse_args()

	if args.protos_dir is None:
		root_dir = os.path.abspath(os.path.dirname(__file__))
		args.protos_dir = os.path.join(root_dir, 'protos')

	if args.output_dir is None:
		args.output_dir = os.getcwd()

	all_proto_files = [file_name.replace("\\", "/") for file_name in collect_files(args.protos_dir, '.proto')]
	proto_files = remove_well_known_protos(all_proto_files)
	CppProtobufGenerator(args, proto_files).run()

class CppProtobufGenerator(object):
	"""Runs protoc for C++ libprotobuf (used in testing)."""

	def __init__(self, args, proto_files):
		self.args = args
		self.proto_files = proto_files

	def run(self):
		out_dir = os.path.join(self.args.output_dir, 'cpp')
		mkdir(out_dir)

		self.__run_generator(out_dir)

		sources = collect_files(out_dir, '.pb.h', '.pb.cc')
		# TODO(wilhuff): strip trailing whitespace?
		post_process_files(
				sources,
				add_copyright
		)

	def __run_generator(self, out_dir):
		"""Invokes protoc using using the default C++ generator."""

		cmd = protoc_command(self.args)
		#--cpp_out=dllexport_decl=FOO_EXPORT:outdir
		cmd.append('--cpp_out=dllexport_decl=FIRESTORE_EXPORT:' + out_dir)
		cmd.append('--grpc_out=' + out_dir) # BITSAUCE
		cmd.append('--plugin=protoc-gen-grpc=' + self.args.grpc_cpp_plugin) # BITSAUCE
		cmd.extend(self.proto_files)

		run_protoc(self.args, cmd)


def protoc_command(args):
	"""Composes the initial protoc command-line including its include path."""
	cmd = [args.protoc]
	if args.include is not None:
		cmd.extend(['-I%s' % path for path in args.include])
	return cmd


def run_protoc(args, cmd):
	"""Actually runs the given protoc command.

	Args:
		args: The command-line args (including pythonpath)
		cmd: The command to run expressed as a list of strings
	"""

	kwargs = {}
	if args.pythonpath:
		env = os.environ.copy()
		old_path = env.get('PYTHONPATH')
		env['PYTHONPATH'] = args.pythonpath
		if old_path is not None:
			env['PYTHONPATH'] += os.pathsep + old_path
		kwargs['env'] = env

	print(" ".join(cmd))
	subprocess.check_call(cmd, **kwargs)


def remove_well_known_protos(filenames):
	"""Remove "well-known" protos for objc and cpp.

	On those platforms we get these for free as a part of the protobuf runtime.
	We only need them for nanopb.

	Args:
		filenames: A list of filenames, each naming a .proto file.

	Returns:
		The filenames with members of google/protobuf removed.
	"""

	return [f for f in filenames if 'protos/google/protobuf/' not in f]


def post_process_files(filenames, *processors):
	for filename in filenames:
		lines = []
		with open(filename, 'r') as fd:
			lines = fd.readlines()

		for processor in processors:
			lines = processor(lines)

		write_file(filename, lines)


def write_file(filename, lines):
	with open(filename, 'w') as fd:
		fd.write(''.join(lines))


def add_copyright(lines):
	"""Adds a copyright notice to the lines."""
	result = [COPYRIGHT_NOTICE, '\n']
	result.extend(lines)
	return result


def collect_files(root_dir, *extensions):
	"""Finds files with the given extensions in the root_dir.

	Args:
		root_dir: The directory from which to start traversing.
		*extensions: Filename extensions (including the leading dot) to find.

	Returns:
		A list of filenames, all starting with root_dir, that have one of the given
		extensions.
	"""
	result = []
	for root, _, files in os.walk(root_dir):
		for basename in files:
			for ext in extensions:
				if basename.endswith(ext):
					filename = os.path.join(root, basename)
					result.append(filename)
	return result


def mkdir(dirname):
	if not os.path.isdir(dirname):
		os.makedirs(dirname)


if __name__ == '__main__':
	main()
